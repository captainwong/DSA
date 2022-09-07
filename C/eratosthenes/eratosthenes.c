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
		   "  tr n file: test if n is a prime by read eratosthenes from file, tr n file\n"
		   , exe);
	exit(1);
}

typedef enum Command {
	W,R,T,TR
}Command;

int main(int argc, char** argv)
{
	Command cmd = T;
	int n;
	char* file = NULL;
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
	} else {
		usage(argv[0]);
	}	

	Bitmap bmp = { 0 };

	switch (cmd) {
	case W:
	case T:
	{
		bitmapInit(&bmp, n);
		bitmapSet(&bmp, 0);
		for (int i = 2; i <= n; i++) {
			if (!bitmapTest(&bmp, i-1)) {
				for (int j = min(46340, i) * min(46340, i); j <= n; j += i) {
					bitmapSet(&bmp, j-1);
				}
			}
		}
		if (cmd == W) {
			if (0 != bitmapDump(&bmp, file)) {
				fprintf(stderr, "dump bitmap to file \"%s\" failed\n", file);
				exit(1);
			}
		} else {
			printf("%d is %s a prime\n", n, bitmapTest(&bmp, n-1) ? "not" : "");
		}
		break;
	}
	case R:
	case TR:
	{
		if (0 != bitmapLoad(&bmp, file)) {
			fprintf(stderr, "load bitmap from file \"%s\" failed\n", file);
			exit(1);
		}
		if (cmd == TR) {
			if (n > bmp.N * 8) {
				fprintf(stderr, "%d is out of bound, file only has %d numbers\n", n, bmp.N * 8);
				exit(1);
			}
			printf("%d is %s a prime\n", n, bitmapTest(&bmp, n-1) ? "not" : "");			
		} else {
			for (int i = 1; i <= bmp.N * 8; i++) {
				if (!bitmapTest(&bmp, i-1)) {
					printf("%d ", i);
				}
			}
		}
		break;
	}
	}

}
