#ifdef USE_QUADRATIC_HASH

#if defined(_MSC_VER) && defined(_DEBUG)
#define AVP_DUMP_MEM_LEAK
#endif

// Necessary includes and defines for memory leak detection:
#ifdef AVP_DUMP_MEM_LEAK
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hash_quadratic.h"

#define WARN_NO_MEM fprintf(stderr, "%s %d No memory\n", __FILE__, __LINE__);


/* -------------------------- hash functions -------------------------------- */

static uint8_t dict_hash_function_seed[16];


/* The default hashing function uses SipHash implementation
 * in siphash.c. */

uint64_t siphash(const uint8_t* in, const size_t inlen, const uint8_t* k);
uint64_t siphash_nocase(const uint8_t* in, const size_t inlen, const uint8_t* k);

void hash_set_hash_function_seed(uint8_t* seed)
{
	memcpy(dict_hash_function_seed, seed, sizeof dict_hash_function_seed);
}

uint64_t hash_gen_hash_function(const void* key, size_t len)
{
	return siphash(key, len, dict_hash_function_seed);
}


/* ----------------------------- API implementation ------------------------- */

static int is_prime(int n) {
	if (n < 2) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	for (int i = 3; i * i <= n; i += 2) {
		if (n % i == 0) return 0;
	}
	return 1;
}

// next prime bigger than n, and in 4k+3 form
// `two-square therorem of Fermat`
static int next_4kp3_prime(int n) {
	while (++n % 4 != 3 || !is_prime(n));
	return n;
}

/* Returns the index of a free slot that can be populated with
 * a hash entry for the given 'key'.
 * If the key already exists, -1 is returned
 * and the optional output parameter may be filled.
 */
static long _hash_find(hash_t* h, const void* key, uint64_t hash, entry_t** existing) {
	long long i = 0;
	long long pos, cur;
#if USE_EXPONETIAL_EXPANDING
	pos = cur = hash & (h->size - 1);
#else
	pos = cur = hash % h->size;
#endif
	if (existing) *existing = NULL;

	sizeof(int);
	sizeof(long long);

	while (h->entries[pos] &&
		   h->entries[pos]->state == ENTRY_STATE_LEGITIMATE &&
		   !hash_compare_keys(h, key, h->entries[pos]->key)) {
		if (i == 46340) {
			int j = 0;
		}
		if (++i % 2) {
			pos = cur + (i + 1) * (i + 1) / 4;
			while (pos >= h->size)
				pos %= h->size;
		} else {
			pos = cur - i * i / 4;
			while (pos < 0)
				pos += h->size;
		}
		if (pos >= h->size) {
			int j = 0;
		}
	}
	if (h->entries[pos] &&
		h->entries[pos]->state == ENTRY_STATE_LEGITIMATE) {
		if (existing) *existing = h->entries[pos];
		return -1;
	}
	return pos;
}


hash_t* hash_create(hash_type_t* type)
{
	hash_t* h = malloc(sizeof *h);
	if (h == NULL) {
		WARN_NO_MEM;
		return NULL;
	}

	h->type = type;
#if USE_EXPONETIAL_EXPANDING
	h->size = 8;
#else
	h->size = next_4kp3_prime(HASH_TABLE_MIN_SIZE);
#endif
	h->used = 0;
	h->entries = calloc(1, sizeof(entry_t*) * h->size);
	if (h->entries == NULL) {
		WARN_NO_MEM;
		free(h);
		return NULL;
	}

	return h;
}

void hash_clear(hash_t* h)
{
	for (unsigned int i = 0; i < h->size; i++) {
		if (h->entries[i]) {
			hash_free_taken_entry(h, h->entries[i]);
			h->entries[i] = NULL;
		}
	}

	h->used = 0;
}

void hash_free(hash_t* h)
{
	hash_clear(h);
	free(h->entries);
	free(h);
}

float hash_load_factor(hash_t* h)
{
	return h->used * 1.0f / h->size;
}

void hash_rehash(hash_t* h)
{
	unsigned long size;
	if (hash_load_factor(h) <= HASH_TABLE_MIN_LOAD_FACTOR) {
#if USE_EXPONETIAL_EXPANDING
		size = h->size / 2;
#else
		size = (unsigned int)(h->size * HASH_TABLE_MIN_LOAD_FACTOR * 2);
#endif
		if (size < HASH_TABLE_MIN_SIZE)
			size = HASH_TABLE_MIN_SIZE;
		if (size == h->size)
			return;
	} else if (hash_load_factor(h) >= HASH_TABLE_MAX_LOAD_FACTOR) {
#if USE_EXPONETIAL_EXPANDING
		size = h->size * 2;
#else
		size = next_4kp3_prime(h->size * 2);
#endif
	} else {
		return;
	}

	hash_t tmph = *h;
	tmph.entries = calloc(1, sizeof(entry_t*) * size);
	if (tmph.entries == NULL) {
		WARN_NO_MEM;
		abort();
	}
	tmph.size = size;
	tmph.used = 0;

	for (unsigned long i = 0; i < h->size; i++) {
		if (h->entries[i]) {
			if (h->entries[i]->state == ENTRY_STATE_LEGITIMATE) {
#if USE_EXPONETIAL_EXPANDING
				uint64_t hash = hash_hash_key(&tmph, h->entries[i]->key) & (size - 1);
#else
				uint64_t hash = hash_hash_key(&tmph, h->entries[i]->key) % size;
#endif
				long idx = _hash_find(&tmph, h->entries[i]->key, hash, NULL);
				assert(idx != -1);
				tmph.entries[idx] = h->entries[i];
				tmph.used++;
			} else {
				hash_free_taken_entry(h, h->entries[i]);
			}
		}
	}
	assert(tmph.used == h->used);

	free(h->entries);
	h->entries = tmph.entries;
	h->size = size;
}

/* Add an element to the target hash table */
int hash_insert(hash_t* h, void* key, void* val)
{
	entry_t* he = hash_insert_raw(h, key, NULL);
	if (!he) return HASH_ERR;
	hash_set_val(h, he, val);
	return HASH_OK;
}

/* Low level add or find:
 * This function adds the entry but instead of setting a value returns the
 * entry_t structure to the user, that will make sure to fill the value
 * field as they wish.
 *
 * This function is also directly exposed to the user API to be called
 * mainly in order to store non-pointers inside the hash value, example:
 *
 * entry = hash_insert_raw(dict,mykey,NULL);
 * if (entry != NULL) hash_set_s64_val(entry,1000);
 *
 * Return values:
 *
 * If key already exists NULL is returned, and "*existing" is populated
 * with the existing entry if existing is not NULL.
 *
 * If key was added, the hash entry is returned to be manipulated by the caller.
 */
entry_t* hash_insert_raw(hash_t* h, void* key, entry_t** existing)
{
	entry_t* he = NULL; 
#if USE_EXPONETIAL_EXPANDING
	uint64_t hash = hash_hash_key(h, key) & (h->size - 1);
#else
	uint64_t hash = hash_hash_key(h, key) % h->size;
#endif

	/* Get the index of the new element, or -1 if
	 * the element already exists. */
	long idx = _hash_find(h, key, hash, existing);
	if (idx == -1) return NULL;

	if (h->entries[idx]) {
		assert(h->entries[idx]->state == ENTRY_STATE_DELETED);
		he = h->entries[idx];
		hash_free_key(h, he);
		hash_free_val(h, he);
	} else {
		he = malloc(sizeof * he);
		if (!he) {
			WARN_NO_MEM;
			return NULL;
		}
	}

	h->entries[idx] = he;
	hash_set_key(h, he, key);
	he->state = ENTRY_STATE_LEGITIMATE;
	h->used++;
	if (hash_load_factor(h) >= HASH_TABLE_MAX_LOAD_FACTOR)
		hash_rehash(h);

	return he;
}

/* Search and remove an element. This is a helper function for
 * hash_remove() and hash_take(), please check the top comment
 * of those functions. */
static entry_t* hash_generic_remove(hash_t* h, const void* key, int nofree) {
	long long i = 0;
	long long pos, cur;

	if (h->used == 0) return NULL;

#if USE_EXPONETIAL_EXPANDING
	pos = cur = hash_hash_key(h, key) & (h->size - 1);
#else
	pos = cur = hash_hash_key(h, key) % h->size;
#endif

	while (h->entries[pos] &&
		   !hash_compare_keys(h, key, h->entries[pos]->key)) {
		if (++i % 2) {
			pos = cur + (i + 1) * (i + 1) / 4;
			if (pos >= h->size)
				pos %= h->size;
		} else {
			pos = cur - i * i / 4;
			while (pos < 0)
				pos += h->size;
		}
	}

	if (h->entries[pos] && h->entries[pos]->state == ENTRY_STATE_LEGITIMATE) {
		if (!nofree) {
			entry_t* he = h->entries[pos];
			h->entries[pos] = malloc(sizeof(entry_t));
			if (!h->entries[pos]) {
				WARN_NO_MEM;
				abort();
			}
			hash_set_key(h, h->entries[pos], he->key);
			hash_set_val(h, h->entries[pos], he->v.val);

			hash_free_taken_entry(h, he);
		}
		h->entries[pos]->state = ENTRY_STATE_DELETED;
		h->used--;
		return h->entries[pos];
	}

	return NULL;
}

/* Remove an element, returning HASH_OK on success or HASH_ERR if the
 * element was not found. */
int hash_remove(hash_t* h, const void* key)
{
	return hash_generic_remove(h, key, 0) ? HASH_OK : HASH_ERR;
}

/* Remove an element from the table, but without actually releasing
 * the key, value and dictionary entry. The dictionary entry is returned
 * if the element was found (and removed from the table), and the user
 * should later call `hash_free_taken_entry()` with it in order to release it.
 * Otherwise if the key is not found, NULL is returned.
 *
 * This function is useful when we want to remove something from the hash
 * table but want to use its value before actually deleting the entry.
 * Without this function the pattern would require two lookups:
 *
 *  entry = hash_find(...);
 *  // Do something with entry
 *  hash_remove(dictionary,entry);
 *
 * Thanks to this function it is possible to avoid this, and use
 * instead:
 *
 * entry = hash_take(dictionary,entry);
 * // Do something with entry
 * hash_free_taken_entry(entry); // <- This does not need to lookup again.
 */
entry_t* hash_take(hash_t* h, const void* key)
{
	return hash_generic_remove(h, key, 1);
}

void hash_free_taken_entry(hash_t* h, entry_t* he)
{
	if (he == NULL) return;
	hash_free_key(h, he);
	hash_free_val(h, he);
	free(he);
}

entry_t* hash_find(hash_t* h, const void* key)
{
	long long i = 0;
	long long pos, cur;

	if (h->used == 0) return NULL;
#if USE_EXPONETIAL_EXPANDING
	pos = cur = hash_hash_key(h, key) & (h->size-1);
#else
	pos = cur = hash_hash_key(h, key) % h->size;
#endif
	while (h->entries[pos] &&
		   !hash_compare_keys(h, key, h->entries[pos]->key)) {
		if (++i % 2) {
			pos = cur + (i + 1) * (i + 1) / 4;
			if (pos >= h->size)
				pos %= h->size;
		} else {
			pos = cur - i * i / 4;
			while (pos < 0)
				pos += h->size;
		}
	}

	if (h->entries[pos] && h->entries[pos]->state == ENTRY_STATE_DELETED) {
		return NULL;
	}

	return h->entries[pos];
}

entry_t* hash_get_random_key(hash_t* h)
{
	entry_t* he = NULL;
	if (h->used == 0) return NULL;
	do {
		he = h->entries[rand() % h->size];
	} while (he == NULL || he->state != ENTRY_STATE_LEGITIMATE);
	return he;
}

void* hash_retrieve_value(hash_t* h, const void* key)
{
	entry_t* he = hash_find(h, key);
	return he ? hash_get_val(he) : NULL;
}


#endif // USE_QUADRATIC_HASH
