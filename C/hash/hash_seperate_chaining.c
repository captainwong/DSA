#ifdef USE_SEPERATE_CHAINING

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

// when used/buckets > 5, table size will double grow
static unsigned int hash_force_resize_ratio = 5;


/* -------------------------- helper functions ---------------------------- */


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
	if (minimal < HASH_INITIAL_SIZE)
		minimal = HASH_INITIAL_SIZE;
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

void hash_clear(hash_t* h) {

}

void hash_free(hash_t* h) {

}

float hash_load_factor(hash_t* h) {
	return 0;
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
		assert(HASH_SIZE(h->size_exp[0]) > (unsigned long)h->rehash_idx);

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
			hash = hash_hash_key(h, he->key) & HASH_SIZE_MASK(h->size_exp[1]);
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

int hash_insert(hash_t* h, void* key, void* val) {
	return 0;
}

entry_t* hash_insert_raw(hash_t* h, void* key, void* val, entry_t** existing) {
	return NULL;
}

int hash_remove(hash_t* h, const void* key) {
	return 0;
}

entry_t* hash_take(hash_t* h, const void* key) {
	return NULL;
}

void hash_free_taken_entry(hash_t* h, entry_t* he) {

}

entry_t* hash_find(hash_t* h, const void* key) {
	return NULL;
}

entry_t* hash_get_random_key(hash_t* h) {
	return NULL;
}

void* hash_retrieve_value(hash_t* h, const void* key) {
	entry_t* he = hash_find(h, key);
	return he ? hash_get_val(he) : NULL;
}


/* ------------------------- private functions ------------------------------ */

// Our hash table capacity is a power of 2.
static signed char _hash_next_exp(unsigned long size) {
	unsigned char exp = HASH_INITIAL_EXP;
	if (size >= LONG_MAX) return 8 * sizeof(long) - 1;
	while (1) {
		if (((unsigned long)1 << exp) >= size)
			return exp;
		exp++;
	}
}



#endif // USE_SEPERATE_CHAINING

