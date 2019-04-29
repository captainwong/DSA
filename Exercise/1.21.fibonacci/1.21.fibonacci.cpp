// 1.21.fibonacci.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include "../../include/dtl/fibnacci.h"
using namespace dtl;

/***测试用******/
#include <assert.h>
#include <time.h>
/*****************/



int main()
{
	printf("testing fib iteration...\n");
	auto t = clock();
	auto r = fibI(64);
	auto e = clock() - t;
	printf("fib iteration result=%lld elapsed %lf ms\n\n", r, e * 1000.0 / CLOCKS_PER_SEC);

	printf("testing fib linear recursion...\n");
	t = clock();
	__int64 prev;
	r = fibL(64, prev);
	e = clock() - t;
	printf("fib linear recursion result=%lld elapsed %lf ms\n\n", r, e * 1000.0 / CLOCKS_PER_SEC);

	printf("testing fib binary recursion...\n");
	t = clock();
	r = fibR(64);
	e = clock() - t;
	printf("fib binary recursion result=%lld elapsed %lf ms\n\n", r, e * 1000.0 / CLOCKS_PER_SEC); // 我就不等了。。。

	
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
