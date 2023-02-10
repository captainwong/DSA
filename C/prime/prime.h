#ifndef __PRIME_H__
#define __PRIME_H__

#pragma once

static int is_prime(int n) {
	if (n < 2) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	for (int i = 3; i * i <= n; i += 2) {
		if (n % i == 0) return 0;
	}
	return 1;
}

static int next_prime(int n) {
	while (!is_prime(++n));
	return n;
}

static int next_4kp3_prime(int n) {
	while (++n % 4 != 3 || !is_prime(n));
	return n;
	
}

#endif
