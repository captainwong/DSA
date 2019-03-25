// 1.12.count_ones.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

//! ͳ������n�Ķ�����չ������λ1��������O(logn)
int countOnes(unsigned int n)
{
	int ones = 0;
	while (0 < n) {
		ones += (n & 1);
		n >>= 1;
	}
	return ones;
}


//! O(countOnes(n)), ������������λ1��ʵ����Ŀ
int countOnes1(unsigned int n)
{
	int ones = 0;
	while (0 < n) {
		ones++;
		n = n & (n - 1);
	}
	return ones;
}


//! 2��c�η�
#define POW(c) (1 << (c))
//! ��2��c�η�Ϊ��λ���飬����ȫ0��ȫ1
#define MASK(c) (((unsigned long) -1) / (POW(POW(c)) + 1))
// MASK(0) = 0x55555555
// MASK(1) = 0x33333333
// MASK(2) = 0x0F0F0F0F
// MASK(3) = 0x00FF00FF
// MASK(4) = 0x0000FFFF

// ���룺n�Ķ�����չ���У���2��c�η�Ϊ��λ���飬������ֵ�Ѿ��ֱ����ԭ����2��c�η�λ��1����Ŀ
// ���̣���2�Ĵη�λ��λ���飬���ڵ�������׽���ۼӣ��ۼ�ֵ��ԭ2��(c+1)�η�λ�͵ؼ�¼
// �����n�Ķ�����չ���У���2��(c+1)�η�λ��λ���飬������ֵ�Ѿ��ֱ����ԭ����2��(c+1)�η�λ��1����Ŀ
#define ROUND(n, c) (((n) & MASK(c)) + (((n) >> POW(c)) & MASK(c)))

//! O(logW), W=O(logn)Ϊ������λ����O(loglogn)��ͨ������������
int countOnes2(unsigned int n)
{
	n = ROUND(n, 0);
	n = ROUND(n, 1);
	n = ROUND(n, 2);
	n = ROUND(n, 3);
	n = ROUND(n, 4);
	return n;
}


const char* simple_bin(unsigned long n)
{
	static char buf[128] = { 0 };
	buf[0] = 0;

	for (int i = sizeof(long) * 8 - 1, j = 0; i >= 0; i--, j++) {
		auto mask = 1 << i;
		buf[j] = (n & mask) ? '1' : '0';
		buf[j + 1] = 0;
	}

	return buf;
}

constexpr auto m1 = (unsigned long)-1;
unsigned long pow(int c) { return 1 << c; }
unsigned long mask(int c) { return m1 / (pow(pow(c)) + 1); }

unsigned long round(unsigned int n, int c) 
{
	printf("round%d n=%d\n", c, n);
	printf("--------------\t----------=FEDCBA9876543210FEDCBA9876543210\n");
	printf("round%d ---n=\t0x%08X=%s\n", c, n, simple_bin(n));
	auto mc = mask(c);
	auto pc = pow(c);
	auto ppc = pow(pow(c));
	printf("round%d mask=\t0x%08X=%s\n", c, mc, simple_bin(mc));
	printf("round%d pow=\t0x%08X=%s\n", c, pc, simple_bin(pc));
	printf("round%d ppc=\t0x%08X=%s\n", c, ppc, simple_bin(ppc));
	auto left = n & mc;
	printf("round%d n&mc=\t0x%08X=%s\n", c, left, simple_bin(left));
	auto right = n >> pc;
	printf("round%d n>>pc=\t0x%08X=%s\n", c, right, simple_bin(right));
	right &= mc;
	printf("round%d &=mc=\t0x%08X=%s\n", c, right, simple_bin(right));
	auto ret = left + right;
	printf("round%d ret=\t0x%08X=%s\n\n", c, ret, simple_bin(ret));
	return ret;
}

//! ��Ч��countOnes2
int countOnes3(unsigned int n)
{
	n = round(n, 0);
	n = round(n, 1);
	n = round(n, 2);
	n = round(n, 3);
	n = round(n, 4);
	return n;
}

int main()
{
	//unsigned long m1 = -1;
	printf("sizeof unsigned long=%zu\n", sizeof m1);
	printf("unsigned long -1=0x%08X=%s\n", m1, simple_bin(m1));
	for (int i = 0; i < 5; i++) {
		auto mask_ = mask(i);
		printf("mask(%d)=%u\n", i, mask_);
		printf("=0x%08X=%s\n", mask_, simple_bin(mask_));
	}

	printf("\n");

	int co = countOnes3(m1);
	assert(co == 32);

	//co = countOnes3(441);
	//assert(co == 6);
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
