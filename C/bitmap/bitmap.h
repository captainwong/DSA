#ifndef __BITMAP_H__
#define __BITMAP_H__

#pragma once

#include <stddef.h> // size_t
#include <errno.h> // E2BIG, ENOMEM

struct bitmap_s {
	unsigned char* M;
	size_t N;
};

typedef struct bitmap_s bitmap_t;

// if success, bitmap object is returned, otherwise check `errno` for error code.
bitmap_t* bitmap_create(size_t N);
// free the bitmap object
void bitmap_free(bitmap_t* bmp);
// set index k to 1
// return 0 for ok, E2BIG for k is too big, ENOMEM for no memory
int bitmap_set(bitmap_t* bmp, size_t k);
// set index k to 0
// return 0 for ok, E2BIG for k is too big, ENOMEM for no memory
int bitmap_clear(bitmap_t* bmp, size_t k);
// check if index k is 1.
// if k is out of bound, 0 is returned.
int bitmap_test(bitmap_t* bmp, size_t k);
// load bmp from file
// check `errno` for error code.
// caller should release the returned object by calling `bitmap_free`
bitmap_t* bitmap_load(const char* file);
// dump bmp to file, return 0 for success, otherwise check `errno` for error code.
int bitmap_dump(bitmap_t* bmp, const char* file);


#endif
