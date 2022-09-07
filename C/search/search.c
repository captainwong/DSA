#include <stdio.h>
#include "../fibonacci/fibonacci.h"

#define PRNIT_PIVOT 1

int binSearch(int* a, int key, int lo, int hi)
{
	while (lo < hi) {
		int mi = (lo + hi) >> 1;
#if PRNIT_PIVOT
		printf("pivot=%d, a[%d]=%d\n", mi, mi, a[mi]);
#endif
		(key < a[mi]) ? (hi = mi) : (lo = mi + 1);
	}
	return lo - 1;
}

int fibSearch(int* a, int key, int lo, int hi)
{
	Fibonacci fib;
	fibInit(&fib, hi - lo);
	while (lo < hi) {
		while (hi - lo < fib.g) {
			fibPrev(&fib);
		}
		int mi = lo + fib.g - 1;
#if PRNIT_PIVOT
		printf("pivot=%d, a[%d]=%d\n", mi, mi, a[mi]);
#endif
		(key < a[mi]) ? (hi = mi) : (lo = mi + 1);
	}
	return --lo;
}


void test(char* name, int(*search)(int*, int, int, int))
{
	printf("Testing %s\n", name);
	int a[7] = { 1,2,3,4,5,6,7 };
	int key = 1;
	printf("searching %d from\n[", key);
	for (int i = 0; i < 7; i++) {
		printf("%s%d", i == 0 ? "" : ", ", a[i]);
	}
	printf("]\n");
	int ret = search(a, key, 0, 7);
	printf("ret=%d\n\n", ret);
}

#define TEST(search) test(#search, search)

int main()
{
	TEST(binSearch);
	TEST(fibSearch);
}