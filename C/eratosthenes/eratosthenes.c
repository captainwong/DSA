#include "../bitmap/bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char* exe)
{
	printf("%s command args\n"
		   "  w n file: write eratosthenes of N numbers to file, n must be a multiple of 8\n"
		   "  r file: read eratosthenes from file and print all primes\n"
		   "  t n: test if n is a prime\n"
		   "  tr n file: test if n is a prime by read eratosthenes from file\n"
		   "  oj n: generate prime table for oj\n"
		   , exe);
	exit(1);
}

typedef enum {
	W, R, T, TR, OJ
}command;

#define TEST_4KP3 0

#if TEST_4KP3
static void test_4k_plus3() {
	const size_t N = 0x00FFFF;
	bitmap_t* bmp = bitmap_create(N);
	bitmap_set(bmp, 0);
	for (size_t i = 2; i <= N; i++) {
		if (!bitmap_test(bmp, i - 1)) {
			for (size_t j = min(46340, i) * min(46340, i); j <= N; j += i) {
				bitmap_set(bmp, j - 1);
			}
		}
	}

	for (size_t i = 3; i < N; i += 4) {
		if (bitmap_test(bmp, i - 1) && i % 4 == 3) {
			printf("%d ", i);
		}
	}
	bitmap_free(bmp);
}
#endif

int main(int argc, char** argv)
{
#if TEST_4KP3
	test_4k_plus3();
	return 0;
#endif

	int n = 0;
	size_t N = 0;
	char* file = NULL;
	bitmap_t* bmp = NULL;
	command cmd = T;

	if (argc < 2) usage(argv[0]);
	if (strcmp("w", argv[1]) == 0) {
		cmd = W;
		if (argc < 4) usage(argv[0]);
		n = atoi(argv[2]);
		if (n % 8) { usage(argv[0]); }
		file = argv[3];
	} else if (strcmp("r", argv[1]) == 0) {
		cmd = R;
		if (argc < 3) usage(argv[0]);
		file = argv[2];
	} else if (strcmp("t", argv[1]) == 0) {
		cmd = T;
		if (argc < 3) usage(argv[0]);
		n = atoi(argv[2]);
	} else if (strcmp("tr", argv[1]) == 0) {
		cmd = TR;
		if (argc < 4) usage(argv[0]);
		n = atoi(argv[2]);
		file = argv[3];
	} else if (strcmp("oj", argv[1]) == 0) {
		cmd = OJ;
		if (argc < 3) usage(argv[0]);
		n = atoi(argv[2]);
	} else {
		usage(argv[0]);
	}

	if (n < 1) {
		fprintf(stderr, "N must bigger than 0");
		return -1;
	}
	N = n;

	switch (cmd) {
	case W:
	case T:
	case OJ:
	{
		bmp = bitmap_create(N);
		bitmap_set(bmp, 0);
		for (size_t i = 2; i <= N; i++) {
			if (!bitmap_test(bmp, i - 1)) {
				for (size_t j = min(46340, i) * min(46340, i); j <= N; j += i) {
					bitmap_set(bmp, j - 1);
				}
			}
		}
		if (cmd == W) {
			if (0 != bitmap_dump(bmp, file)) {
				fprintf(stderr, "dump bitmap to file \"%s\" failed\n", file);
				exit(1);
			}
		} else if (cmd == OJ) {
			printf("static const int PRIME_%d[%d]={0", N, N);
			for (size_t i = 0; i < N - 1; i++) {
				printf(", %d", !bitmap_test(bmp, i));
			}
			printf("};\n");
		} else { // T
			printf("%d is %s a prime\n", N, bitmap_test(bmp, N - 1) ? "not" : "");
		}
		break;
	}
	case R:
	case TR:
	{
		bmp = bitmap_load(file);
		if (!bmp) {
			fprintf(stderr, "load bitmap from file \"%s\" failed\n", file);
			exit(1);
		}
		if (cmd == TR) {
			if (N > bmp->N * 8) {
				fprintf(stderr, "%d is out of bound, file only has %d numbers\n", N, bmp->N * 8);
				exit(1);
			}
			printf("%d is %sa prime\n", N, bitmap_test(bmp, N - 1) ? "not " : "");
		} else {
			for (size_t i = 1; i <= bmp->N * 8; i++) {
				if (!bitmap_test(bmp, i - 1)) {
					printf("%d ", i);
				}
			}
		}
		break;
	}
	}

	bitmap_free(bmp);
	return 0;
}
