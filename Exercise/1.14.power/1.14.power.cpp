// 1.14.power.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <assert.h>

// 时间复杂度 O(n) = O(2^r), r为n的比特位数，空间复杂度O(1)
__int64 power2BF_I(int n)
{
	__int64 pow = 1;
	while (0 < n--) {
		pow <<= 1;
	}
	return pow;
}

// 时间复杂度同上，但空间复杂度提高至O(n)
__int64 power2BF_R(int n)
{
	return (n < 1) ? 1 : power2BF_R(n - 1) << 2;
}

inline __int64 sqr(__int64 a) { return a * a; }

// 幂函数2^n算法，优化递归，n>=0
// 时间复杂度O(logn) = O(r), r为输入指数n的比特位数
__int64 power2(int n)
{
	if (0 == n) { return 1; }
	return (n & 1) ? (sqr(power2(n >> 1)) << 1) : sqr(power2(n >> 1));
}

// 幂函数 power2 迭代版， O(logn)
__int64 power2_I(int n)
{
	__int64 pow = 1;
	__int64 p = 2;

	while (n) {
		if (n & 1) { pow *= p; }
		n >>= 1;
		p *= p;
	}

	return pow;
}

int main()
{
	auto r = power2_I(7);
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
