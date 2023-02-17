#ifdef USE_SEPERATE_CHAINING

#if defined(_MSC_VER) && defined(_DEBUG)
#define AVP_DUMP_MEM_LEAK
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <sys/time.h>
#endif
#include "hash_seperate_chaining.h"

/* -------------------------- helper functions ---------------------------- */

static long long time_ms() {
#ifdef _WIN32
	// Based on https://doxygen.postgresql.org/gettimeofday_8c_source.html
	// Link is broken, use this https://github.com/microsoft/vcpkg/blob/master/ports/gettimeofday/gettimeofday.h
	static const uint64_t epoch = 116444736000000000Ui64;
	FILETIME file_time;
	ULARGE_INTEGER ularge;

	GetSystemTimeAsFileTime(&file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;
	int64_t tv_sec = (int64_t)((ularge.QuadPart - epoch) / 10000000L);
	int32_t tv_usec = (int32_t)(((ularge.QuadPart - epoch) % 10000000L) / 10);
	return (((long long)tv_sec) * 1000) + (tv_usec / 1000);
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
#endif
}

/* -------------------------- private prototypes ---------------------------- */

static int _hash_expand_if_needed(hash_t* h);
static signed char _hash_next_exp(unsigned long size);
static long _hash_key_index(hash_t* h, const void* key, uint64_t hash, entry_t** existing);
static int _hash_init(hash_t* h, hash_type_t* type);


/* -------------------------- hash functions -------------------------------- */

static uint8_t dict_hash_function_seed[16];

void hash_set_hash_function_seed(uint8_t* seed) {
	memcpy(dict_hash_function_seed, seed, sizeof(dict_hash_function_seed));
}

/* The default hashing function uses SipHash implementation
 * in siphash.c. */

uint64_t siphash(const uint8_t* in, const size_t inlen, const uint8_t* k);
uint64_t siphash_nocase(const uint8_t* in, const size_t inlen, const uint8_t* k);

uint64_t hash_gen_hash_function(const void* key, size_t len) {
	return siphash(key, len, dict_hash_function_seed);
}

uint64_t hash_gen_nocase_hash_function(const void* key, size_t len) {
	return siphash_nocase(key, len, dict_hash_function_seed);
}



/* ----------------------------- API implementation ------------------------- */

static void _hash_reset(hash_t* h, int idx) {
	h->entries[idx] = NULL;
	h->size_exp[idx] = -1;
	h->used[idx] = 0;
}

// Initialize the hash table
static int _hash_init(hash_t* h, hash_type_t* type) {
	_hash_reset(h, 0);
	_hash_reset(h, 1);
	h->type = type;
	h->rehash_idx = -1;
	h->pause_rehash = 0;
	return HASH_OK;
}

// Create a new hash table
hash_t* hash_create(hash_type_t* type) {
	hash_t* h = malloc(sizeof * h);
	_hash_init(h, type);
	return h;
}

// Resize the table to the minimal size that contains all the elements,
// but with the invariant of a USED/BUCKET ratio near to <=1
int hash_resize(hash_t* h) {
	unsigned long minimal;
	if (hash_is_rehashing(h)) return HASH_ERR;
	minimal = h->used[0];
	if (minimal < HASH_TABLE_INITIAL_SIZE)
		minimal = HASH_TABLE_INITIAL_SIZE;
	return hash_expand(h, minimal);
}

// Try allocating memory and zero it, and return NULL if failed.
// `usable` is set to usable size if non-NULL.
static void* try_calloc_usable(size_t size, size_t* usable) {
	void* ptr = calloc(1, size);
	if (ptr == NULL) return NULL;
	if (usable)*usable = size;
	return ptr;
}

// Try allocating memory and zero it, and return NULL if failed.
static void* try_calloc(size_t size) {
	return try_calloc_usable(size, NULL);
}

// Expand or create the hash table,
// when malloc_failed is non-MULL, it'll avoid panic if malloc fails (in witch
//   case it'll be set to 1)
// Return HASH_OK if expand was performed, or HASH_ERR if skipped.
static int _hash_expand(hash_t* h, unsigned long size, int* malloc_failed) {
	if (malloc_failed) *malloc_failed = 0;

	// the size is invliad if it is smaller than the number of
	// elements already inside the hash table
	if (hash_is_rehashing(h) || h->used[0] > size)
		return HASH_ERR;

	// the new hash table
	entry_t** table;
	unsigned long used;
	signed char size_exp = _hash_next_exp(size);

	// detect overflows
	size_t newsize = (size_t)(1ul << size_exp);
	if (newsize < size || newsize * sizeof(entry_t*) < newsize)
		return HASH_ERR;

	// rehashing to the same table size is not useful
	if (size_exp == h->size_exp[0]) return HASH_ERR;

	// allocate the new hash table and initialize all pointers to NULL
	if (malloc_failed) {
		table = try_calloc(newsize * sizeof(entry_t*));
		*malloc_failed = table == NULL;
		if (*malloc_failed) return HASH_ERR;
	} else {
		table = calloc(1, newsize * sizeof(entry_t*));
	}

	used = 0;

	// Is this the first initialization? If so it's not really a rehashing,
	// we just set the first hash table so that it can accept keys.
	if (h->entries[0] == NULL) {
		h->size_exp[0] = size_exp;
		h->used[0] = used;
		h->entries[0] = table;
	} else {
		// Prepare a second hash table for incremental rehashing
		h->size_exp[1] = size_exp;
		h->used[1] = used;
		h->entries[1] = table;
		h->rehash_idx = 0;
	}
	return HASH_OK;
}

int hash_expand(hash_t* h, unsigned long size) {
	return _hash_expand(h, size, NULL);
}

int hash_try_expand(hash_t* h, unsigned long size) {
	int malloc_failed;
	_hash_expand(h, size, &malloc_failed);
	return malloc_failed ? HASH_ERR : HASH_OK;
}

/* Perform N stpes of incremental rehashing.
 * Returns 1 if there are still keys to move from the old to the new hash table,
 *   otherwise 0 is returned.
 * Note that a rehashing step consists in moving a bucket (that may have more
 * than one key as we use chaining) from the old to the new hash table, however
 * since part of the hash table may composed of empty spaces, it is not
 * guaranteed that this function will rehash even a single bucket, since it 
 * will visit at max N*10 empty buckets in total, otherwise the amount of
 * work it does would be unbound and the function may block for a long time. 
 */
int hash_rehash(hash_t* h, int n) {
	int empty_visits = n * 10; // max number of empty buckets to visit.
	if (!hash_is_rehashing(h)) return 0;

	while (n-- && h->used[0] != 0) {
		entry_t* he, * nexthe;

		// Note that rehash_idx can't overflow as we are sure there are more
		// elements because used[0] != 0
		assert(HASH_TABLE_SIZE(h->size_exp[0]) > (unsigned long)h->rehash_idx);

		while (h->entries[0][h->rehash_idx] == NULL) {
			h->rehash_idx++;
			if (--empty_visits == 0) return 1;
		}

		he = h->entries[0][h->rehash_idx];

		// move all the keys in this bucket from the old to the new hash table
		while (he) {
			uint64_t hash;
			nexthe = he->next;
			// get the index in the new hash table
			hash = hash_hash_key(h, he->key) & HASH_TABLE_SIZE_MASK(h->size_exp[1]);
			he->next = h->entries[1][hash];
			h->entries[1][hash] = he;
			h->used[0]--;
			h->used[1]++;
			he = nexthe;
		}

		h->entries[0][h->rehash_idx] = NULL;
		h->rehash_idx++;
	}

	// check if we already rehashed the whole table
	if (h->used[0] == 0) {
		free(h->entries[0]);
		// copy the new table onto the old one
		h->entries[0] = h->entries[1];
		h->used[0] = h->used[1];
		h->size_exp[0] = h->size_exp[1];
		_hash_reset(h, 1);
		h->rehash_idx = -1;
		return 0;
	}

	// more to rehash
	return 1;
}

// Rehash in ms+`delta` milliseconds. The value of `delta` is larger
// than 0, and is smaller than 1 in most cases. The exact upper bound
// depends on the running time of hash_rehash(d, 100).
int hash_rehash_ms(hash_t* h, int ms) {
	if (h->pause_rehash > 0) return 0;
	long long start = time_ms();
	int rehashes = 0;

	while (hash_rehash(h, 100)) {
		rehashes += 100;
		if (time_ms() - start > ms) break;
	}
	return rehashes;
}

// Add an element to the target hash table
int hash_insert(hash_t* h, void* key, void* val) {
	entry_t* entry = hash_insert_raw(h, key, NULL);
	if (!entry) return HASH_ERR;
	hash_set_val(h, entry, val);
	return HASH_OK;
}

/* This function performs just a step of rehashing, and only if hashing has
 * not been paused for our hash table. When we have iterators in the
 * middle of a rehashing we can't mess with the two hash tables otherwise
 * some elements can be missed or duplicated.
 * 
 * This function is called by common lookup or update operations in the
 * dictionary so that the hash table automatically migrates from H1 to H2
 * while it is actively used.
 */
static void _hash_rehash_step(hash_t* h) {
	if (h->pause_rehash == 0) hash_rehash(h, 1);
}

/* Low level add or find:
 * This function adds the entry but instead of setting a value and 
 * returns the `entry_t` to the user, that will make sure to fill the
 * value field as they wish.
 * 
 * This function is also directly exposed to the user API to be called
 * mainly in order to store non-pointers inside the hash value, example:
 * 
 * entry = hash_add_raw(h, key, NULL);
 * if (entry) hash_set_s64_val(h, entry, 1000);
 * 
 * Return values:
 * 
 * If key already exists NULL is returned, and `*existing` is populated
 * with the existing entry if `existing` is not NULL.
 * 
 * If key was added, the hash entry is returned to be manipulated by the caller.
 */
entry_t* hash_insert_raw(hash_t* h, void* key, entry_t** existing) {
	long idx;
	entry_t* he;
	int htidx;

	if (hash_is_rehashing(h)) _hash_rehash_step(h);

	// Get the index of the new element, or -1 if the element already exists.
	if ((idx = _hash_key_index(h, key, hash_hash_key(h, key), existing)) == -1)
		return NULL;

	// Allocates the memory and store the new entry.
	// Insert the element in top, with the assumption that in a database
	// system it is more likely that recently added entries are accessed
	// more frequently.
	htidx = hash_is_rehashing(h) ? 1 : 0;
	he = malloc(sizeof * he);
	he->next = h->entries[htidx][idx];
	h->entries[htidx][idx] = he;
	h->used[htidx]++;

	// set the hash entry fields
	hash_set_key(h, he, key);
	return he;
}

/* Add or Find:
 * `hash_insert_or_find` is simply a version of `hash_add_raw` that always
 * returns the hash entry of the specified key, even if the key already
 * exists and can't be added (in that case the entry of the already
 * existing key is returned)
 */
entry_t* hash_insert_or_find(hash_t* h, void* key) {
	entry_t* entry, * existing;
	entry = hash_insert_raw(h, key, &existing);
	return entry ? entry : existing;
}

/* Add or Overwirte:
 * Add an element, discarding the old value if the key already exists.
 * Return 1 if the key was added from scratch, 0 if there was already
 * an element with such key and `hash_replace` just performed a value update
 * operation.
 */
int hash_replace(hash_t* h, void* key, void* val) {
	entry_t* entry, * existing, auxentry;
	// try to add the element. If the key does not exists `hash_add` will succeed.
	entry = hash_insert_raw(h, key, &existing);
	if (entry) {
		hash_set_val(h, entry, val);
		return 1;
	}

	/* Set the new value and free the old one. Note that it is important
	 * to do that in this order, as the value may just be exatly the same
	 * as the previous one. In this context, think to reference counting,
	 * you want to increment (set), and then decrement (free), and not the
	 * reverse.
	 */
	auxentry = *existing;
	hash_set_val(h, existing, val);
	hash_free_val(h, &auxentry);
	return 0;
}

// Search and remove an element. This is a helper function for
// `hash_remove` and `hash_take`, please check the top comment of those functions.
static entry_t* _hash_generic_remove(hash_t* h, const void* key, int nofree) {
	uint64_t hash, idx;
	entry_t* he, * prev;
	int htidx;

	// dict is empty
	if (hash_used(h) == 0) return NULL;

	if (hash_is_rehashing(h)) _hash_rehash_step(h);
	hash = hash_hash_key(h, key);

	for (htidx = 0; htidx <= 1; htidx++) {
		idx = hash & HASH_TABLE_SIZE_MASK(h->size_exp[htidx]);
		he = h->entries[htidx][idx];
		prev = NULL;
		while (he) {
			if (hash_key_equals(h, key, he->key)) {
				if (prev)
					prev->next = he->next;
				else
					h->entries[htidx][idx] = he->next;
				if (!nofree)
					hash_free_taken_entry(h, he);
				h->used[htidx]--;
				return he; // if nofree==0, `he` is already `free`ed, 
				           // its a `dangling pointer` pointing to nothing valid.
				           // and should only be used to check with NULL.
						   // and should not be used other ways.
			}

			// search continue, save the prev entry to `prev`
			prev = he;
			he = he->next;
		}
		if (!hash_is_rehashing(h)) break; // if not rehashing, entries[1] is NULL
	}
	return NULL; // Not found
}

// Remove an element, returning HASH_OK on success or HASH_ERR if
// the element was not found.
int hash_remove(hash_t* h, const void* key) {
	return _hash_generic_remove(h, key, 0) ? HASH_OK : HASH_ERR;
}

/* Remove an element from the table, but without actually releasing
 * the key, value and entry. The dictionary entry is returned
 * if the element was found (and unlinked from the table), and the user
 * should later call `hash_free_taken_entry` with it in order to release it.
 * Otherwise if the key is not found, NULL is returned.
 * 
 * This function is useful when we want to remove something from the hash table
 * but want to use its value before actually deleting the entry.
 * Without this function the pattern would require two lookups:
 * 
 *   entry = hash_find(...);
 *   // do something with entry
 *   hash_remove(h, entry);
 * 
 * Thanks to this function it is possible to avoid this, and use instead:
 *   entry = hash_take(...);
 *   // do something with entry
 *   hash_free_taken_entry(h, entry); // <- this does not need to lookup again.
 */
entry_t* hash_take(hash_t* h, const void* key) {
	return _hash_generic_remove(h, key, 1);
}

// You need to call this function to really free the entry after a call
// to `hash_take`. It's safe to call this function with `he` is NULL.
void hash_free_taken_entry(hash_t* h, entry_t* he) {
	if (he == NULL) return;
	hash_free_key(h, he);
	hash_free_val(h, he);
	free(he);
}

// Destroy an entire slot
static int _hash_clear(hash_t* h, int htidx, void(callback)(hash_t*)) {
	// free all the elements
	for (unsigned long i = 0; i < HASH_TABLE_SIZE(h->size_exp[htidx]) && h->used[htidx] > 0; i++) {
		entry_t* he, * next;
		if (callback && (i & 0xFFFF) == 0) callback(h);
		if ((he = h->entries[htidx][i]) == NULL) continue;
		while (he) {
			next = he->next;
			hash_free_taken_entry(h, he);
			h->used[htidx]--;
			he = next;
		}
	}
	// free the table and the allocated cache structure
	free(h->entries[htidx]);
	// re-initialize the table
	_hash_reset(h, htidx);
	return HASH_OK; // never fails
}

// Clear & Release the hash table
void hash_free(hash_t* h) {
	_hash_clear(h, 0, NULL);
	_hash_clear(h, 0, NULL);
	free(h);
}

// Find a entry with key
entry_t* hash_find(hash_t* h, const void* key) {
	entry_t* he;
	uint64_t hash, idx, htidx;
	if (hash_used(h) == 0) return NULL;
	if (hash_is_rehashing(h)) _hash_rehash_step(h);
	hash = hash_hash_key(h, key);
	for (htidx = 0; htidx <= 1; htidx++) {
		idx = hash & HASH_TABLE_SIZE_MASK(h->size_exp[htidx]);
		he = h->entries[htidx][idx];
		while (he) {
			if (hash_key_equals(h, key, he->key))
				return he;
			he = he->next;
		}
		if (!hash_is_rehashing(h)) return NULL; // if not rehashing, entries[1] is NULL
	}
	return NULL;
}

// Get a entry's value if key exists
void* hash_retrieve_value(hash_t* h, const void* key) {
	entry_t* he = hash_find(h, key);
	return he ? hash_get_val(he) : NULL;
}

// Return a random entry from the hash table. Useful to implement randomized algorithms.
entry_t* hash_get_random_key(hash_t* h) {
	entry_t* he, * head;
	unsigned long idx;
	int listlen, listele;

	if (hash_used(h) == 0) return NULL;
	if (hash_is_rehashing(h)) _hash_rehash_step(h);
	if (hash_is_rehashing(h)) {
		unsigned long s0 = HASH_TABLE_SIZE(h->size_exp[0]);
		do {
			// we are sure there are no elements in indexes from 0 to rehash_idx-1
			idx = h->rehash_idx + (random_ulong() % (hash_slots(h) - h->rehash_idx));
			he = (idx >= s0) ? h->entries[1][idx - s0] : h->entries[0][idx];
		} while (he == NULL);
	} else {
		unsigned long m = HASH_TABLE_SIZE_MASK(h->size_exp[0]);
		do {
			idx = random_ulong() & m;
			he = h->entries[0][idx];
		} while (he == NULL);
	}

	// Now we found a non empty bucket, but is is a linked list and we need to 
	// get a random element from the list.
	// The only sane way to do so is counting the elements and select a random index.
	listlen = 0;
	head = he;
	while (he) {
		he = he->next;
		listlen++;
	}
	listele = rand() % listlen;
	he = head;
	while (listele--)
		he = he->next;
	return he;
}

#define HASH_STATS_VECTLEN 50
static size_t _hash_get_stats_ht(char* buf, size_t bufsize, hash_t* h, int htidx) {
	unsigned long slots = 0, chainlen, maxchainlen = 0, totchainlen = 0;
	unsigned long clvector[HASH_STATS_VECTLEN] = { 0 };
	size_t r = 0;
	if (h->used[htidx] == 0) {
		return snprintf(buf, bufsize, "No stats available for empty hash table\n");
	}

	for (unsigned long i = 0; i < HASH_TABLE_SIZE(h->size_exp[htidx]); i++) {
		entry_t* he;
		if (h->entries[htidx][i] == NULL) {
			clvector[0]++;
			continue;
		}
		slots++;
		chainlen = 0;
		he = h->entries[htidx][i];
		while (he) {
			chainlen++;
			he = he->next;
		}
		clvector[(chainlen < HASH_STATS_VECTLEN) ? chainlen : (HASH_STATS_VECTLEN - 1)]++;
		if (chainlen > maxchainlen)
			maxchainlen = chainlen;
		totchainlen += chainlen;
	}

	r += snprintf(buf + r, bufsize - r,
				  "Hash table %d stats (%s):\n"
				  " table size: %lu\n"
				  " number of elements: %lu\n"
				  " different slots: %lu\n"
				  " max chain length: %lu\n"
				  " avg chain length(counted): %.02f\n"
				  " avg chain length(computed): %.02f\n"
				  " Chain length distribution:\n",
				  htidx, (htidx == 0) ? "main hash table" : "rehashing target",
				  HASH_TABLE_SIZE(h->size_exp[htidx]), h->used[htidx], slots, maxchainlen,
				  (float)totchainlen / slots, (float)h->used[htidx] / slots);

	for (int i = 0; i < HASH_STATS_VECTLEN - 1; i++) {
		if (clvector[i] == 0) continue;
		if (r >= bufsize) break;
		r += snprintf(buf + r, bufsize - r,
					  "   %ld: %ld (%.02f%%)\n",
					  i, clvector[i], clvector[i] * 100.f / HASH_TABLE_SIZE(h->size_exp[htidx]));
	}
	// make sure there is a NULL term at the end
	if (bufsize) buf[bufsize - 1] = '\0';
	return strlen(buf);
}

void hash_get_stats(char* buf, size_t bufsize, hash_t* h) {
	char* origin = buf;
	size_t origin_size = bufsize;
	size_t l = _hash_get_stats_ht(buf, bufsize, h, 0);
	buf += l;
	bufsize -= l;
	if (hash_is_rehashing(h) && bufsize > 0)
		_hash_get_stats_ht(buf, bufsize, h, 1);
	if (origin_size) // make sure there is a NULL term at the end
		origin[origin_size - 1] = '\0';
}


/* ------------------------- private functions ------------------------------ */

// Our hash table capacity is a power of 2.
static signed char _hash_next_exp(unsigned long size) {
	unsigned char exp = HASH_TABLE_INITIAL_EXP;
	if (size >= LONG_MAX) return 8 * sizeof(long) - 1;
	while (1) {
		if (((unsigned long)1 << exp) >= size)
			return exp;
		exp++;
	}
}

/* Returns the index of a free slot that can be populated with
 * a hash entry for the given `key`.
 * If the key already exists, -1 is returned, and the optional output
 * parameter may be filled.
 * 
 * Note that if we are in the process of rehashing the hash table, the
 * index is always returned in the context of the second (new) hash table.
 */
static long _hash_key_index(hash_t* h, const void* key, uint64_t hash, entry_t** existing) {
	unsigned long idx, htidx;
	entry_t* he;
	if (existing) *existing = NULL;

	// expand the hash table if needed
	if (_hash_expand_if_needed(h) == HASH_ERR) return -1;
	for (htidx = 0; htidx <= 1; htidx++) {
		idx = hash & HASH_TABLE_SIZE_MASK(h->size_exp[htidx]);
		// search if this slot does not already contain the given key
		he = h->entries[htidx][idx];
		while (he) {
			if (hash_key_equals(h, key, he->key)) {
				if (existing) *existing = he;
				return -1;
			}
			he = he->next;
		}
		if (!hash_is_rehashing(h)) break; // if not rehashing, slot[1] is empty.
	}
	return idx;
}

// Expand the hash table if needed
static int _hash_expand_if_needed(hash_t* h) {
	// Incremental rehashing already in progress. Return.
	if (hash_is_rehashing(h)) return HASH_OK;

	// If the hash table is empty expand it to the initial size
	if (HASH_TABLE_SIZE(h->size_exp[0]) == 0)
		return hash_expand(h, HASH_TABLE_INITIAL_SIZE);

	// If we reached the 1:1 ratio, we resize doubling the number of buckets.
	if (h->used[0] >= HASH_TABLE_SIZE(h->size_exp[0])) {
		return hash_expand(h, h->used[0] + 1);
	}
	return HASH_OK;
}


#endif // USE_SEPERATE_CHAINING

