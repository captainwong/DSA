/* from <Data Structuresand Algorithm Analysis In C> 2nd Edition, by Mark Allen Weiss
* http://users.cis.fiu.edu/~weiss/dsaa_c2e/files.html
*
* from 浙江大学MOOC 《数据结构》 陈越，何钦铭
* https://www.icourse163.org/course/ZJU-93001?tid=1468077441
*
* from redis/src/dict.h, dict.c
* https://github.com/redis/redis
*
*
* Hash Set using seperate chaining.
*/

#ifndef __HASH_SEPERATE_CHAINING_H__
#define __HASH_SEPERATE_CHAINING_H__

#pragma once

#ifdef USE_SEPERATE_CHAINING

#include <stdint.h>

#define HASH_OK 0
#define HASH_ERR 1

#define HASH_SIZE(exp) ((exp == -1) ? 0 : (unsigned long)1 << (exp))
#define HASH_SIZE_MASK(exp) ((exp == -1) ? 0 : HASH_SIZE(exp) - 1)

// This is the initial size of every hash table
#ifndef HASH_INITIAL_EXP
#define HASH_INITIAL_EXP 2
#endif
#define HASH_INITIAL_SIZE (1 << (HASH_INITIAL_EXP))

typedef struct entry_t {
	void* key;
	union {
		void* val;
		uint64_t u64;
		int64_t s64;
		double d;
	}v;
	struct entry_t* next;
}entry_t;

typedef struct hash_s hash_t;

typedef struct {
	uint64_t(*hash)(const void* key);
	int (*key_compare)(hash_t* h, const void* k1, const void* k2);
	void* (*key_dup)(hash_t* h, const void* key);
	void (*key_free)(hash_t* h, void* key);
	void* (*val_dup)(hash_t* h, const void* obj);
	void (*val_free)(hash_t* h, void* obj);
}hash_type_t;

struct hash_s {
	hash_type_t* type;
	entry_t** entries[2];
	unsigned long used[2];

	long rehash_idx; // rehashing not in progress if rehashidx == -1

	// Keep small vals at end for optimal (minimal) struct padding
	int16_t pause_rehash; // If >0 rehashing is paused (<0 indicates coding error)
	signed char size_exp[2]; // Exponent of size. (size = 1 << exp)
};


/* ------------------------------- Macros ------------------------------------*/

#define hash_free_val(h, entry) \
	do { \
		if ((entry)->v.val && (h)->type->val_free) \
			(h)->type->val_free((h), (entry)->v.val); \
	} while (0);

#define hash_set_val(h, entry, _val_) \
	do { \
		if ((h)->type->val_dup) \
			(entry)->v.val = (h)->type->val_dup((h), (_val_)); \
		else \
			(entry)->v.val = (_val_); \
	} while (0);

#define hash_set_s64_val(entry, _val_) \
	do { \
		(entry)->v.s64 = (_val_); \
	} while (0);

#define hash_set_u64_val(entry, _val_) \
	do { \
		(entry)->v.u64 = (_val_); \
	} while (0);

#define hash_set_double_val(entry, _val_) \
	do { \
		(entry)->v.d = (_val_); \
	} while (0);

#define hash_free_key(h, entry) \
	do { \
		if ((entry)->key && (h)->type->key_free) \
			(h)->type->key_free((h), (entry)->key); \
	} while (0);

#define hash_set_key(h, entry, _key_) \
	do { \
		if ((h)->type->key_dup) \
			(entry)->key = (h)->type->key_dup((h), (_key_)); \
		else \
			(entry)->key = (_key_); \
	} while (0);

#define hash_compare_keys(h, k1, k2) \
	(((h)->type->key_compare) ? \
		(h)->type->key_compare((h), k1, k2) : \
		(k1) == (k2))

#define hash_hash_key(h, key) (h)->type->hash((key))
#define hash_get_key(e) ((e)->key)
#define hash_get_val(e) ((e)->v.val)
#define hash_get_s64_val(e) ((e)->v.s64)
#define hash_get_u64_val(e) ((e)->v.u64)
#define hash_get_double_val(e) ((e)->v.d)
#define hash_slots(h) (HASH_SIZE((d)->size_exp[0]) + HASH_SIZE((d)->size_exp[1]))
#define hash_size(h) ((h)->used[0] + (h)->used[1])
#define hash_is_rehashing(h) ((h)->rehash_idx != -1)
#define hash_pause_rehash(h) ((h)->pause_rehash++)
#define hash_resume_rehash(h) ((h)->pause_rehash--)


/* API */

void hash_set_hash_function_seed(uint8_t* seed);
uint64_t hash_gen_hash_function(const void* key, size_t len);
uint64_t hash_gen_nocase_hash_function(const void* key, size_t len);
hash_t* hash_create(hash_type_t* type);
int hash_expand(hash_t* h, unsigned long size);
int hash_try_expand(hash_t* h, unsigned long size);
int hash_resize(hash_t* h);
int hash_rehash(hash_t* h, int n);
int hash_insert(hash_t* h, void* key, void* val);
entry_t* hash_insert_raw(hash_t* h, void* key, void* val, entry_t** existing);
int hash_remove(hash_t* h, const void* key);
entry_t* hash_take(hash_t* h, const void* key);
void hash_free_taken_entry(hash_t* h, entry_t* he);
entry_t* hash_find(hash_t* h, const void* key);
entry_t* hash_get_random_key(hash_t* h);
void* hash_retrieve_value(hash_t* h, const void* key);
void hash_clear(hash_t* h);
void hash_free(hash_t* h);


#endif // USE_SEPERATE_CHAINING

#endif
