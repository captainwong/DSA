#include "bitmap.h"
#include <assert.h>

#include <math.h>
#include <stdint.h>
#include <float.h>
#include <stdio.h>

int main()
{
	bitmap_t* bmp = bitmap_create(13);
	assert(bmp);

	printf("%d\n", DBL_MAX > UINT64_MAX);
	//uint64_t n = sqrtl(UINT64_MAX);
	uint64_t n = 4294967295;
	uint64_t nn = n * n;
	printf("UINT64_MAX=%llu=0x%llX, square=%llu=0x%llX, n*n=%llu=0x%llX\n", UINT64_MAX, UINT64_MAX, n, n, nn, nn);

	for (size_t i = 0; i < 13; i++) {
		assert(bitmap_test(bmp, i) == 0);
	}

	for (size_t i = 0; i < 13; i++) {
		bitmap_set(bmp, i);
		assert(bitmap_test(bmp, i) == 1);
	}

	for (size_t i = 0; i < 256; i++) {
		bitmap_clear(bmp, i);
		assert(bitmap_test(bmp, i) == 0);
	}

	bitmap_free(bmp);
}