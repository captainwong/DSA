
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#ifndef _OJ_
#include <stdlib.h>
#endif // !_OJ_


//struct fastio
//{
//	static constexpr int sz = 1 << 10;
//	char inbuf[sz];
//	char outbuf[sz];
//	fastio()
//	{
//		setvbuf(stdin, inbuf, _IOFBF, sz);
//		setvbuf(stdout, outbuf, _IOFBF, sz);
//	}
//}__io;


struct Light {
	int x = 0;
	int y = 0;
};

static constexpr int MAX_LIGHT = 4000000;

Light Lights[MAX_LIGHT] = {};
Light TmpLights[(MAX_LIGHT >> 1) + 1] = {};

void mergeSortX(Light* lights, int lo, int hi);
void mergeX(Light* lights, int lo, int mi, int hi);

long sequenceYInside(Light* lights, int lo, int hi);
long sequenceYBetween(Light* lights, int lo, int mi, int hi);

long invertionYInside(Light* lights, int lo, int hi);
long invertionYBetween(Light* lights, int lo, int mi, int hi);

int main()
{
	int n = 0;
	if (scanf("%d\n", &n) != 1)
		return 0;

	for (int i = 0; i < n; i++) {
		if (scanf("%d %d\n", &Lights[i].x, &Lights[i].y) != 2)
			return 0;
	}

	mergeSortX(Lights, 0, n);
	// ˳��Խⷨ
	//auto sum = sequenceYInside(Lights, 0, n);

	// 2018-8-9 21:19:23 
	// ����Խⷨ
	// �������������������� ˳������� = ���е���������ϵ����� - ���������
	// ���е���������ϵ���������ô���أ�������ѧ��ʦ�Ĺײİ�찴��ס�ˣ�����
	// ����Ϊ C(n, 2)
	// = A(n, 2) / 2
	// = n! / (n - 2)! / 2
	// = n(n-1) / 2
	auto sum = invertionYInside(Lights, 0, n);
	sum = (long)n * (n - 1) / 2 - sum;


	printf("%ld\n", sum);

#ifndef _OJ_
	system("pause");
#endif // !_OJ_

}

void mergeSortX(Light * lights, int lo, int hi)
{
	if (hi - lo < 2) { return; }
	int mi = (lo + hi) / 2;
	mergeSortX(lights, lo, mi);
	mergeSortX(lights, mi, hi);
	mergeX(lights, lo, mi, hi);
}

void mergeX(Light * lights, int lo, int mi, int hi)
{
	auto A = lights + lo;
	auto B = TmpLights;
	auto C = lights + mi;

	auto lb = mi - lo;
	auto lc = hi - mi;

	/*for (int i = 0; i < lb; i++) {
		B[i] = A[i];
	}*/

	memcpy(B, A, lb * sizeof(Light));

	for (int ia = 0, ib = 0, ic = 0; (ib < lb) || (ic < lc); ) {
		if ((ib < lb) && (!(ic < lc) || (B[ib].x < C[ic].x))) { A[ia++] = B[ib++]; }
		if ((ic < lc) && (!(ib < lb) || (C[ic].x < B[ib].x))) { A[ia++] = C[ic++]; }
	}
}

long sequenceYInside(Light * lights, int lo, int hi)
{
	if (hi - lo < 2) { return 0; }
	int mi = (lo + hi) / 2;
	auto a = sequenceYInside(lights, lo, mi);
	auto b = sequenceYInside(lights, mi, hi);
	auto c = sequenceYBetween(lights, lo, mi, hi);
	return a + b + c;
}

long sequenceYBetween(Light * lights, int lo, int mi, int hi)
{
	auto A = lights + lo;
	auto B = TmpLights;
	auto C = lights + mi;

	auto lb = mi - lo;
	auto lc = hi - mi;

	memcpy(B, A, lb * sizeof(Light));

	long sum = 0;

	for (int ia = 0, ib = 0, ic = 0; (ib < lb) || (ic < lc); ) {
		if ((ib < lb) && (!(ic < lc) || (B[ib].y < C[ic].y))) { 
			if (ic < lc) {
				// sum += lb + 1;
				sum += lc - ic;

				// 2018-8-8 01:44:22 
				// �Ϸ�������ĺ�95AC�������
				// lc - ic ΪC[ic]֮��ĵ�����������֪��C[ic]��������֮�����е�y������B[ib].y�����lc - ic ��Ϊ˳�������
				// BUT!!!
				// Ϊʲôlb + 1���ǣ�
				// lb + 1 ΪB[ib](�������������еĵ�������Ҳ�Ǹ�C[ic].y����˳��ԣ�Ϊëֻ��20AC������

				// 2018-8-8 01:49:29
				// got it
				// ��B[ib]����ĵ㣬ÿ�ζ���ͳ�ƣ��ᵼ�³�����ʵ����
				// ֻ�д�C[ic]����ͳ�ƣ�������ʵ����
			}
			A[ia++] = B[ib++];
		}

		if ((ic < lc) && (!(ib < lb) || (C[ic].y < B[ib].y))) { 
			A[ia++] = C[ic++]; 
		}
	}

	return sum;
}

long invertionYInside(Light * lights, int lo, int hi)
{
	if (hi - lo < 2) { return 0; }
	int mi = (lo + hi) / 2;
	auto a = invertionYInside(lights, lo, mi);
	auto b = invertionYInside(lights, mi, hi);
	auto c = invertionYBetween(lights, lo, mi, hi);
	return a + b + c;
}

long invertionYBetween(Light * lights, int lo, int mi, int hi)
{
	auto A = lights + lo;
	auto B = TmpLights;
	auto C = lights + mi;

	auto lb = mi - lo;
	auto lc = hi - mi;

	memcpy(B, A, lb * sizeof(Light));

	long sum = 0;

	for (int ia = 0, ib = 0, ic = 0; (ib < lb) || (ic < lc); ) {
		if ((ib < lb) && (!(ic < lc) || (B[ib].y < C[ic].y))) {
			A[ia++] = B[ib++];
		}

		if ((ic < lc) && (!(ib < lb) || (C[ic].y < B[ib].y))) {
			if (ib < lb) {
				sum += lb - ib;
			}

			A[ia++] = C[ic++];
		}
	}

	return sum;
}
