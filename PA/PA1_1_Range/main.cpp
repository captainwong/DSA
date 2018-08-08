// https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1142
/*
	��Χ��ѯ(Range)
	Descriptioin
	Let S be a set of n integral points on the x - axis.For each given interval[a, b], you are asked to count the points lying inside.

	Input
	The first line contains two integers : n(size of S) and m(the number of queries).

	The second line enumerates all the n points in S.

	Each of the following m lines consists of two integers a and b and defines an query interval[a, b].

	Output
	The number of points in S lying inside each of the m query intervals.

	Example
	Input

	5 2
	1 3 7 9 11
	4 6
	7 12
	Output

	0
	3
	Restrictions
	0 <= n, m <= 5 * 10 ^ 5

	For each query interval[a, b], it is guaranteed that a <= b.

	Points in S are distinct from each other.

	Coordinates of each point as well as the query interval boundaries a and b are non - negative integers not greater than 10 ^ 7.

	Time: 2 sec

	Memory : 256 MB

	����
	��������n���㣬������һ������[a, b]���Լ����������ڵĵ�����

	����
	��һ�а��������������������n����ѯ�Ĵ���m��

	�ڶ��а���n������Ϊ����������ꡣ

	����m�У�������������������ѯ��������ұ߽�a��b��

	���
	��ÿ�β�ѯ��������ڱ�����[a, b]�ڵ�ĸ�����

	����
	��Ӣ������

	����
	0 �� n, m �� 5��105

	����ÿ�β�ѯ������[a, b]������a �� b

	��������껥��

	��������ꡢ��ѯ����ı߽�a��b����Ϊ������10 ^ 7�ķǸ�����

	ʱ�䣺2 sec

	�ڴ棺256 MB
*/

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