#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"


static int expand(bitmap_t* bmp, size_t k) {
	size_t n;
	void* m;

	if (k < 8 * bmp->N) 
		return 0;
	if (k >= SIZE_MAX / 8)
		return E2BIG;
	n = (k * 2 + 7) / 8;
	m = realloc(bmp->M, n);
	if (m == NULL)
		return ENOMEM;
	memset((char*)m + bmp->N, 0, n - bmp->N);
	bmp->M = m;
	bmp->N = n;

	return 0;
}

bitmap_t* bitmap_create(size_t N) {
	bitmap_t* bmp = malloc(sizeof * bmp);
	if (bmp == NULL) return NULL;
	bmp->M = calloc(1, bmp->N = (N + 7) / 8);
	if (bmp->M == NULL) {
		free(bmp);
		return NULL;
	}
	return bmp;
}

void bitmap_free(bitmap_t* bmp) {
	free(bmp->M);
	free(bmp);
}

int bitmap_set(bitmap_t* bmp, size_t k) {
	int r = expand(bmp, k);
	if (r) return r;
	bmp->M[k >> 3] |= (0x80 >> (k & 0x07));
	return 0;
}

int bitmap_clear(bitmap_t* bmp, size_t k) {
	int r = expand(bmp, k);
	if (r) return r;
	bmp->M[k >> 3] &= ~(0x80 >> (k & 0x07));
	return 0;
}

int bitmap_test(bitmap_t* bmp, size_t k) {
	if (k / 8 >= bmp->N) return 0;
	return !!(bmp->M[k >> 3] & (0x80 >> (k & 0x07)));
}

bitmap_t* bitmap_load(const char* file) {
	FILE* f;
	long len;
	bitmap_t* bmp;

	f = fopen(file, "rb");
	if (!f) { return NULL; }
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	if (len <= 0) return NULL;
	bmp = bitmap_create(len * 8);
	if (bmp == NULL) {
		fclose(f);
		return NULL;
	}
	fseek(f, 0, SEEK_SET);
	fread(bmp->M, 1, len, f);
	fclose(f);
	return bmp;
}

int bitmap_dump(bitmap_t* bmp, const char* file) {
	FILE* f = fopen(file, "wb");
	if (!f) { return errno; }
	fwrite(bmp->M, 1, bmp->N, f);
	fclose(f);
	return 0;
}
