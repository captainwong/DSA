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

#include "../testcase.h"

#define N 32

void gen_testcase(int n)
{
	system("mkdir testcase");
	system("cd testcase && del *.in *.out testcase.zip && cd ..");
	for (int i = 1; i <= n; i++) {
		gen_in_out(i,
				   [i](FILE* f) {
					   fprintf(f, "%d", i);
				   },
				   [i](FILE* f) {
					   fprintf(f, "%lld", fibI(i));
				   });
	}
	system("cd testcase && zip testcase.zip *.in *.out");
}

void gen_testcase_pro()
{
	system("mkdir testcase");
	system("cd testcase && del *.in *.out testcase.zip && cd ..");

	int arr[10];
	arr[0] = 1;
	arr[9] = 64;

	for (int i = 1; i < 9; i++) {
		arr[i] = rand() % 64;
	}

	qsort(arr, 10, sizeof(int), [](const void* a, const void* b) {
		int a1 = *(const int*)a;
		int a2 = *(const int*)b;
		return a1 - a2;
	});

	for (int i = 1; i < 10; i++) {
		gen_in_out(i,
				   [i, arr](FILE* f) {
					   fprintf(f, "%d\n", arr[i]);
				   },
				   [i, arr](FILE* f) {
					   fprintf(f, "%lld\n", fibI(arr[i]));
				   });
	}

	system("cd testcase && zip testcase.zip *.in *.out");
}


int main()
{
	//gen_testcase(32);
	gen_testcase_pro();
	return 0;

	printf("testing fib iteration...\n");
	auto t = clock();
	auto r = fibI(N);
	auto e = clock() - t;
	printf("fib iteration result=%lld elapsed %lf ms\n\n", r, e * 1000.0 / CLOCKS_PER_SEC);

	printf("testing fib linear recursion...\n");
	t = clock();
	__int64 prev;
	r = fibL(N, prev);
	e = clock() - t;
	printf("fib linear recursion result=%lld elapsed %lf ms\n\n", r, e * 1000.0 / CLOCKS_PER_SEC);

	printf("testing fib binary recursion...\n");
	t = clock();
	r = fibR(N);
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
