// 1.26.shift.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>

/***测试用******/
#include <assert.h>
#include <time.h>
/*****************/

template <typename T>
void swap(T&a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

// 数组倒置（多递归基递归版）
void reverse_R(int* A, int lo, int hi)
{
	if (lo < hi) {
		swap(A[lo], A[hi]);
		reverse_R(A, lo + 1, hi - 1);
	}
}

// 数组倒置（迭代版）
void reverse_I(int* A, int lo, int hi)
{
	while (lo < hi) {
		swap(A[lo++], A[hi--]);
	}
}

void reverse(int *A, int n)
{
	reverse_I(A, 0, n - 1);
}

// 数组循环左移 O(3n)
int shift2(int* A, int n, int k)
{
	k %= n;
	reverse(A, k);
	reverse(A + k, n - k);
	reverse(A, n);
	return 3 * n;
}

int main()
{
	int A[] = { 0,1,2,3,4,5,6,7,8 };

	shift2(A, 9, 3);

	int B[] = { 3,4,5,6,7,8,0,1,2 };

	auto equals = [](int* A, int* B, int len) {
		for (int i = 0; i < len; i++) {
			if (A[i] != B[i]) { return false; }
		}
		return true;
	};

	assert(equals(A, B, 9));
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
