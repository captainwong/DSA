// 1.27.ackermann.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>

/***测试用******/
#include <assert.h>
/*****************/


// 阿克曼函数 https://zh.wikipedia.org/zh-hans/%E9%98%BF%E5%85%8B%E6%9B%BC%E5%87%BD%E6%95%B8

// m,n都是非负整数
__int64 ackermann(__int64 m, __int64 n)
{
	if (m == 0) { return n + 1; }
	if (n == 0) { return ackermann(m - 1, 1); }
	return ackermann(m - 1, ackermann(m, n - 1));
}

// 借助 1.14 power_I函数
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
	for (int n = 0; n < 5; n++) {
		assert(ackermann(0, n) == (n + 1));
		assert(ackermann(1, n) == (n + 2));
		assert(ackermann(2, n) == (2 * (n + 3) - 3));
		assert(ackermann(3, n) == (power2_I(n + 3) - 3));
	}

	assert(ackermann(4, 0) == 13);
	assert(ackermann(4, 1) == 65533); // stack overflow!!!
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
