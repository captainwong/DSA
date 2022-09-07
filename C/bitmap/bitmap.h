#ifndef __BITMAP_H__
#define __BITMAP_H__

#pragma once

typedef struct Bitmap {
	unsigned char* M;
	long N;
}Bitmap;


int bitmapInit(Bitmap* bitmap, int N);
void bitmapRelease(Bitmap* bitmap);
void bitmapSet(Bitmap* bitmap, int k);
void bitmapClear(Bitmap* bitmap, int k);
int bitmapTest(Bitmap* bitmap, int k);
// load bitmap from file, return 0 for success, -1 for fail
int bitmapLoad(Bitmap* bitmap, char* file);
// dump bitmap to file, return 0 for success, -1 for fail
int bitmapDump(Bitmap* bitmap, char* file);


#endif
