#include "fibonacci.h"
#include <stdio.h>

int main()
{
	Fibonacci fib;
	fibInit(&fib, 0);
	for (int i = 1; i <= 20; i++) {
		printf("#%2d=%d\n", i, fibNext(&fib));
	}
	puts("\n");
	for (int i = 19; i >= 1; i--) {
		printf("#%2d=%d\n", i, fibPrev(&fib));
	}
}