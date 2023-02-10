/* from <Data Structuresand Algorithm Analysis In C> 2nd Edition, by Mark Allen Weiss
* http://users.cis.fiu.edu/~weiss/dsaa_c2e/files.html
*
* from 浙江大学MOOC 《数据结构》 陈越，何钦铭
* https://www.icourse163.org/course/ZJU-93001?tid=1468077441
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

#define HASH_TABLE_MIN_SIZE 11
#define HASH_TABLE_MAX_LOAD_FACTOR 0.75f
#define HASH_TABLE_MIN_LOAD_FACTOR 0.2f

typedef int element_t;
typedef unsigned int index_t;
typedef index_t position_t;

typedef struct hash_s* hash_t;

hash_t hash_create(unsigned int size);
void hash_free(hash_t h);
float hash_load_factor(hash_t h);
void hash_rehash(hash_t h);
void hash_insert(hash_t h, element_t key);
void hash_remove(hash_t h, element_t key);
position_t hash_find(hash_t h, element_t key);
element_t hash_retrieve(hash_t h, position_t p);


#endif
