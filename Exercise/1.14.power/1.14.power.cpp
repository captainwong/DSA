// 1.14.power.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <assert.h>

// ʱ�临�Ӷ� O(n) = O(2^r), rΪn�ı���λ�����ռ临�Ӷ�O(1)
__int64 power2BF_I(int n)
{
	__int64 pow = 1;
	while (0 < n--) {
		pow <<= 1;
	}
	return pow;
}

// ʱ�临�Ӷ�ͬ�ϣ����ռ临�Ӷ������O(n)
__int64 power2BF_R(int n)
{
	return (n < 1) ? 1 : power2BF_R(n - 1) << 2;
}

inline __int64 sqr(__int64 a) { return a * a; }

// �ݺ���2^n�㷨���Ż��ݹ飬n>=0
// ʱ�临�Ӷ�O(logn) = O(r), rΪ����ָ��n�ı���λ��
__int64 power2(int n)
{
	if (0 == n) { return 1; }
	return (n & 1) ? (sqr(power2(n >> 1)) << 1) : sqr(power2(n >> 1));
}

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
