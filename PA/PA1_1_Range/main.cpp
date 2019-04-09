#define  _CRT_SECURE_NO_WARNINGS


//#include <iostream>
//#include <sstream>
//#include <string>
//using namespace std;
#include <stdio.h>
#include "vector_implementation.h"


#ifndef _OJ_
#include <stdarg.h>
class Log
{
public:
	static void Print(const char* format, ...)
	{
		va_list arg_ptr;
		va_start(arg_ptr, format);
		vfprintf(stdout, format, arg_ptr);
		va_end(arg_ptr);
	}
};
#else
class Log
{
public:
	static void Print(const char* format, ...)
	{}
};
#endif

static bool is_valid_range(int a)
{
	return a >= 0 && a <= 5 * 100000;
}

static bool is_valid_value(int a)
{
	return a >= 0 && a <= 10000000;
}

int main(int argc, char* argv[])
{
	int n, m;
	if (scanf("%d %d\n", &n, &m) != 2)
		return 0;

	if (!is_valid_range(m) || !is_valid_range(n)) {
		return 0;
	}

	//int *A = new int[n];
	//memset(A, 0, n * sizeof(int));
	Vector<int> A;


	for (int i = 0; i < n; i++) {
		int value = 0;
		if (scanf("%d ", &value) != 1) {
			return 0;
		}
		if (!is_valid_value(value)) {
			return 0;
		}
		A.insert(value);
	}

	A.sort();
	if (A.uniquify() > 0)
		return 0;

	Log::Print("Elems of A:\n");
#ifndef _OJ_
	for (int i = 0; i < A.size(); i++) {
		Log::Print("%d ", A[i]);
	}
	Log::Print("\n");
#endif

	int a, b;
	for (int i = 0; i < m; i++) {
		if (scanf("%d %d\n", &a, &b) != 2) {
			return 0;
		}

		if (a > b) {
			return 0;
		}

		if (!is_valid_value(a) || !is_valid_value(b)) {
			return 0;
		}


		Log::Print("%d %d\n", a, b);


		int r1 = A.search(a);
		int r2 = A.search(b);

		if (r1 != -1 && A[r1] == a) {
			r1--;
		}

		if (r2 == -1 && b > A[A.size() - 1]) {
			r2 = A.size();
		}

		Log::Print("%d %d\n", r1, r2);

		printf("%d\n", r2 - r1);

	}

	return 0;
}