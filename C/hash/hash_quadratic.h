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
* Hash Set using open addressing with quadratic probing by alternating signs.
* Hash size is alwasy a prime in 4k+3 form.
* with `insert` operations, `rehash` might be done to 
*   make sure load factor is under 0.75
* With `remove` operations, `rehash` is `suggested` to be done by user to save space.
*/

#ifndef __HASH_QUADRATIC_H__
#define __HASH_QUADRATIC_H__

#pragma once

#ifdef USE_QUADRATIC_HASH

#include <stdint.h>

#define USE_EXPONETIAL_EXPANDING 1

#define HASH_OK 0
#define HASH_ERR 1

#if USE_EXPONETIAL_EXPANDING
#define HASH_TABLE_MIN_SIZE 8
#else
#define HASH_TABLE_MIN_SIZE 11
#endif
#define HASH_TABLE_MAX_LOAD_FACTOR 0.75f
#define HASH_TABLE_MIN_LOAD_FACTOR 0.2f

enum entry_state {
	ENTRY_STATE_LEGITIMATE,
	ENTRY_STATE_DELETED,
};

typedef struct {
	void* key;
	union {
		void* val;
		uint64_t u64;
		int64_t s64;
		double d;
	}v;
	enum entry_state state;
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
	entry_t** entries;
	unsigned int size;
	unsigned int used;
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


/* API */

void hash_set_hash_function_seed(uint8_t* seed);
uint64_t hash_gen_hash_function(const void* key, size_t len);
hash_t* hash_create(hash_type_t* type);
void hash_clear(hash_t* h);
void hash_free(hash_t* h);
float hash_load_factor(hash_t* h);
void hash_rehash(hash_t* h);
int hash_insert(hash_t* h, void* key, void* val);
entry_t* hash_insert_raw(hash_t* h, void* key, entry_t** existing);
int hash_remove(hash_t* h, const void* key);
entry_t* hash_take(hash_t* h, const void* key);
void hash_free_taken_entry(hash_t* h, entry_t* he);
entry_t* hash_find(hash_t* h, const void* key);
entry_t* hash_get_random_key(hash_t* h);
void* hash_retrieve_value(hash_t* h, const void* key);

#endif // USE_QUADRATIC_HASH

#endif
