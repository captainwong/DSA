#ifndef __FIBONACCI_H__
#define __FIBONACCI_H__

#pragma once


typedef struct Fibonacci {
	int f, g;
}Fibonacci;

static inline int fibNext(Fibonacci* fib) {
	int g = fib->g;
	g += fib->f;
	fib->f = fib->g;
	fib->g = g;
	return fib->g;
}

static inline int fibInit(Fibonacci* fib, int n) {
	fib->f = 1; fib->g = 0;
	while (fib->g < n) {
		fibNext(fib);
	}
	return fib->g;
}

static inline int fibGet(Fibonacci* fib) {
	return fib->g;
}

static inline int fibPrev(Fibonacci* fib) {
	int f = fib->g - fib->f;
	fib->g = fib->f;
	fib->f = f;
	return fib->g;
}


#endif
