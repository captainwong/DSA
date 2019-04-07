// 1.25.gcd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <assert.h>


// 欧几里得版求两数的最大公约数 O(log(a+b))
__int64 gcd_euclidean(__int64 a, __int64 b)
{
	return b ? gcd_euclidean(b, a % b) : a;
}

// 欧几里得算法迭代版 O(log(a+b))
__int64 gcd_euclidean_I(__int64 a, __int64 b)
{
	while (b) {
		auto c = a % b;
		a = b;
		b = c;
	}
	return a;
}

namespace my
{

__int64 gcd_cn(__int64 a, __int64 b)
{
	__int64 p = 1; // 1
	while (true) {
		if ((a & 1) || (b & 1)) { // 2
			while (true) {
				auto t = a > b ? (a - b) : (b - a); // 5
				if (t == 0) { return a * p; } // 6

				while (true) {
					if (t & 1) { // 7
						if (a >= b) { // 10
							a = t;
						} else {
							b = t;
						}
						break;
					} else {
						t /= 2; // 8
					}
				}
			}
		} else { // 3
			p *= 2;
			a /= 2;
			b /= 2;
		}
	}
}

__int64 gcd_cn_v2(__int64 a, __int64 b)
{
	__int64 p = 1; // 1

	while (!((a & 1) || (b & 1))) {
		p <<= 1;
		a >>= 1;
		b >>= 1;
	}

	while (true) {
		auto t = a > b ? (a - b) : (b - a); // 5
		if (t == 0) { return a * p; } // 6

		while (true) {
			if (t & 1) { // 7
				if (a >= b) { // 10
					a = t;
				} else {
					b = t;
				}
				break;
			} else {
				t >>= 1; // 8
			}
		}
	}

	return 0;
}
}

namespace textbook
{

// 中华更相减损术 O(log(a + b))
__int64 gcd_cn(__int64 a, __int64 b)
{
	__int64 r = 0; // a 和 b 的 2^r 形式的公因子

	while (!((a & 1) || (b & 1))) { // 若 a 和 b 都是偶数，则同时除2，并累加至 r
		r++; 
		a >>= 1;
		b >>= 1;
	} // 以下，a 和 b 至多其一为偶数

	while (true) {
		while (!(a & 1)) { a >>= 1; } // 若a偶b奇，则剔除a的所有因子2
		while (!(b & 1)) { b >>= 1; } // 若b偶a奇，则剔除b的所有因子2
		(a > b) ? a = a - b : b = b - a; // 简化为：gcd(max(a, b) - min(a, b), min(a, b))
		if (0 == a) { return b << r; } // 简化至平凡情况：gcd(0, b) = b
		if (0 == b) { return a << r; } // 简化至平凡情况：gcd(a, 0) = a
	}
}
}


int main()
{
	printf("%lld %lld %lld %lld\n", gcd_euclidean(1, 1), my::gcd_cn(1, 1), my::gcd_cn_v2(1, 1), textbook::gcd_cn(1, 1));
	printf("%lld %lld %lld %lld\n", gcd_euclidean(1, 2), my::gcd_cn(1, 2), my::gcd_cn_v2(1, 2), textbook::gcd_cn(1, 2));
	printf("%lld %lld %lld %lld\n", gcd_euclidean(2, 1), my::gcd_cn(2, 1), my::gcd_cn_v2(2, 1), textbook::gcd_cn(2, 1));
	printf("%lld %lld %lld %lld\n", gcd_euclidean(8, 6), my::gcd_cn(8, 6), my::gcd_cn_v2(8, 6), textbook::gcd_cn(8, 6));
	printf("%lld %lld %lld %lld\n", gcd_euclidean(28, 36), my::gcd_cn(28, 36), my::gcd_cn_v2(28, 36), textbook::gcd_cn(28, 36));
	printf("%lld %lld %lld %lld\n", gcd_euclidean(38, 46), my::gcd_cn(38, 46), my::gcd_cn_v2(38, 46), textbook::gcd_cn(38, 46));
	printf("%lld %lld %lld %lld\n", gcd_euclidean(78, 123), my::gcd_cn(78, 123), my::gcd_cn_v2(78, 123), textbook::gcd_cn(78, 123));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
