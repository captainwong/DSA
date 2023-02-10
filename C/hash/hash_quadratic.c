#include "hash_quadratic.h"
#include <stdlib.h>
#include <stdio.h>


typedef enum {
	EMPTY,
	LEGITIMATE,
	DELETED,
}entry_state_t;

typedef struct {
	element_t key;
	entry_state_t state;
}entry_t;

struct hash_s {
	unsigned int size;
	unsigned int used;
	entry_t* entries;
};


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

static index_t hash(element_t key, unsigned int size) {
	return key % size;
}

hash_t hash_create(unsigned int size)
{
	hash_t h;
	unsigned int i;

	h = malloc(sizeof(struct hash_s));
	if (h == NULL) {
		fprintf(stderr, "No memory\n");
		abort();
	}

	h->size = next_4kp3_prime(size);
	h->used = 0;
	h->entries = malloc(sizeof(entry_t) * h->size);
	if (h->entries == NULL) {
		fprintf(stderr, "No memory\n");
		abort();
	}

	for (i = 0; i < h->size; i++) {
		h->entries[i].state = EMPTY;
	}

	return h;
}

void hash_free(hash_t h)
{
	free(h->entries);
	free(h);
}

float hash_load_factor(hash_t h)
{
	return h->used * 1.0f / h->size;
}

void hash_rehash(hash_t h)
{
	unsigned int size, j = 0;
	if (hash_load_factor(h) <= HASH_TABLE_MIN_LOAD_FACTOR) {
		size = (unsigned int)(h->size * HASH_TABLE_MIN_LOAD_FACTOR * 2);
		if (size < HASH_TABLE_MIN_SIZE)
			size = HASH_TABLE_MIN_SIZE;
		if (size == h->size)
			return;
	} else if (hash_load_factor(h) >= HASH_TABLE_MAX_LOAD_FACTOR) {
		size = next_4kp3_prime(h->size * 2);
	} else {
		return;
	}

	entry_t* entries = malloc(sizeof(entry_t) * size);
	if (entries == NULL) {
		fprintf(stderr, "No memory\n");
		abort();
	}

	for (position_t i = 0; i < h->size; i++) {
		if (h->entries[i].state == LEGITIMATE) {
			entries[j].key = h->entries[i].key;
			entries[j].state = LEGITIMATE;
			j++;
		}
	}

	while (j < size) {
		entries[j++].state = EMPTY;
	}

	free(h->entries);
	h->entries = entries;
	h->size = size;
}

void hash_insert(hash_t h, element_t key)
{
	position_t pos = hash_find(h, key);
	if (h->entries[pos].state != LEGITIMATE) {
		h->entries[pos].key = key;
		h->entries[pos].state = LEGITIMATE;
		++h->used;
		if (hash_load_factor(h) >= HASH_TABLE_MAX_LOAD_FACTOR)
			hash_rehash(h);
	}
}

void hash_remove(hash_t h, element_t key)
{
	position_t pos = hash_find(h, key);
	if (h->entries[pos].key == key && h->entries[pos].state == LEGITIMATE) {
		h->entries[pos].state = DELETED;
		--h->used;
	}
}

position_t hash_find(hash_t h, element_t key)
{
	int i = 0;
	position_t pos, cur;
	pos = cur = hash(key, h->size);
	while (h->entries[pos].state != EMPTY && h->entries[pos].key != key) {
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

	return pos;
}

element_t hash_retrieve(hash_t h, position_t p)
{
	return h->entries[p].key;
}

