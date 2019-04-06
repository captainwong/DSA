// 1.14.power.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>

/***测试用******/
#include <assert.h>
#include <time.h>
#include <random>
#include <cmath>
/*****************/


// n>=0

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
	return (n < 1) ? 1 : power2BF_R(n - 1) << 1;
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

// 扩展到 a^n
__int64 power(__int64 a, int n)
{
	__int64 pow = 1;
	__int64 p = a;
	while (n) {
		if (n & 1) { pow *= p; }
		n >>= 1;
		p *= p;
	}
	return pow;
}

// 扩展到模指数运算（快速幂取模）
// 参考《离散数学及其应用》第七版 Kenneth H.Rosen 
//	第4章 数论和密码学
//	  4.2 整数表示和算法 
//	    4.2.4 模指数运算
// 求 a^n % m，其中 a,n,m都是大整数
__int64 modular_exponentiation(__int64 a, __int64 n, __int64 m)
{
	__int64 mod = 1;
	__int64 p = a % m;

	while (n) {
		if (n & 1) { mod = (mod * p) % m; }
		p = (p * p) % m;
		n >>= 1;
	}

	return mod;
}


namespace test
{

// 求 2^n，分别测试power2BF_I、power2BF_R、power2、power2_I的性能
void test_power2()
{
	// 测试一千万次取均值
	constexpr int TEST_TIME = 10000000;
	// TEST_TIME个n
	auto n = new int[TEST_TIME];

	// 初始化TEST_TIME个n为随机数，范围[32, 63]
	std::mt19937 engine;
	std::uniform_int_distribution<int> di(32, 63);
	for (int i = 0; i < TEST_TIME; i++) {
		n[i] = di(engine);
	}

	// 正确性测试
	printf("assertion test begin...\n");
	clock_t begin = clock();
	for (int i = 0; i < 100; i++) {
		__int64 pow = static_cast<__int64>(std::pow(2, n[i]));
		assert(power2BF_I(n[i]) == pow);
		assert(power2BF_R(n[i]) == pow);
		assert(power2(n[i]) == pow);
		assert(power2_I(n[i]) == pow);
	}
	auto elapse = clock() - begin;
	printf("assertion test elapsed %lf ms, avg %lf ms\n\n", elapse * 1000.0 / CLOCKS_PER_SEC, elapse * 1000.0 / TEST_TIME/ CLOCKS_PER_SEC);

	// 性能测试1：power2BF_I
	printf("performance test for power2BF_I begin...\n");
	begin = clock();
	for (int i = 0; i < TEST_TIME; i++) {
		power2BF_I(n[i]);
	}
	elapse = clock() - begin;
	printf("performance test for power2BF_I elapsed %lf ms, avg %lf ms\n\n", elapse * 1000.0 / CLOCKS_PER_SEC, elapse * 1000.0 / TEST_TIME / CLOCKS_PER_SEC);

	// 性能测试2：power2BF_R
	printf("performance test for power2BF_R begin...\n");
	begin = clock();
	for (int i = 0; i < TEST_TIME; i++) {
		power2BF_R(n[i]);
	}
	elapse = clock() - begin;
	printf("performance test for power2BF_R elapsed %lf ms, avg %lf ms\n\n", elapse * 1000.0 / CLOCKS_PER_SEC, elapse * 1000.0 / TEST_TIME / CLOCKS_PER_SEC);

	// 性能测试3：power2
	printf("performance test for power2 begin...\n");
	begin = clock();
	for (int i = 0; i < TEST_TIME; i++) {
		power2(n[i]);
	}
	elapse = clock() - begin;
	printf("performance test for power2 elapsed %lf ms, avg %lf ms\n\n", elapse * 1000.0 / CLOCKS_PER_SEC, elapse * 1000.0 / TEST_TIME / CLOCKS_PER_SEC);

	// 性能测试4：power2_I
	printf("performance test for power2_I begin...\n");
	begin = clock();
	for (int i = 0; i < TEST_TIME; i++) {
		power2_I(n[i]);
	}
	elapse = clock() - begin;
	printf("performance test for power2_I elapsed %lf ms, avg %lf ms\n\n", elapse * 1000.0 / CLOCKS_PER_SEC, elapse * 1000.0 / TEST_TIME / CLOCKS_PER_SEC);


	delete[] n;
}

}

int main()
{
	//auto r = power2_I(10);
	//auto m = modular_exponentiation(3, 644, 645);
	//assert(m == 36);

	test::test_power2();
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
