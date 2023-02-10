#include <stdio.h>
#include <assert.h>


#define USE_QUADRATIC_HASH

#ifdef USE_QUADRATIC_HASH
#include "hash_quadratic.h"
#else
#include "hash_seperate_chaining.h"
#endif

#define TEST_NUM 400

int main()
{
	hash_t h = hash_create(10);
	assert(h);

	for (index_t i = 0; i < TEST_NUM; i++) {
		hash_insert(h, i);
	}

	for (index_t i = 0; i < TEST_NUM; i++) {
		if (hash_retrieve(h, hash_find(h, i)) != i) {
			printf("Error at %u\n", i);
		}
	}

	hash_free(h);
}
