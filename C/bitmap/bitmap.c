#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int expand(Bitmap* bmp, int k)
{
	if (k < 8 * bmp->N) return 0;
	int n = bmp->N;
	void* p = bmp->M;
	int ret = bitmapInit(bmp, 2 * k);
	if (ret != 0) return ret;
	memcpy(bmp->M, p, n);
	free(p);
	return 0;
}

int bitmapInit(Bitmap* bmp, int N)
{
	bmp->M = malloc(bmp->N = (N + 7) / 8);
	if (bmp->M == NULL) { return -1; }
	memset(bmp->M, 0, bmp->N);
	return 0;
}

void bitmapRelease(Bitmap* bmp)
{
	if (bmp && bmp->M) {
		free(bmp->M);
		bmp->M = NULL;
	}
}

void bitmapSet(Bitmap* bmp, int k)
{
	expand(bmp, k);
	bmp->M[k >> 3] |= (0x80 >> (k & 0x07));
}

void bitmapClear(Bitmap* bmp, int k)
{
	expand(bmp, k);
	bmp->M[k >> 3] &= ~(0x80 >> (k & 0x07));
}

int bitmapTest(Bitmap* bmp, int k)
{
	return bmp->M[k >> 3] & (0x80 >> (k & 0x07));
}

int bitmapLoad(Bitmap* bmp, char* file)
{
	FILE* f = fopen(file, "rb");
	if (!f) { return -1; }
	bitmapRelease(bmp);
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	if (len > 0) {
		int ret = bitmapInit(bmp, len * 8);
		if (ret != 0) { fclose(f); return ret; }
		fseek(f, 0, SEEK_SET);
		fread(bmp->M, 1, len, f);
		fclose(f);
	}
	return 0;
}

int bitmapDump(Bitmap* bmp, char* file)
{
	FILE* f = fopen(file, "wb");
	if (!f) { return -1; }
	fwrite(bmp->M, sizeof(char), bmp->N, f);
	fclose(f);
	return 0;
}
