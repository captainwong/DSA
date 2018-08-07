// https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1144

/*
����(LightHouse)
Description
As shown in the following figure, If another lighthouse is in gray area, they can beacon each other.



For example, in following figure, (B, R) is a pair of lighthouse which can beacon each other, while (B, G), (R, G) are NOT.



Input
1st line: N

2nd ~ (N + 1)th line: each line is X Y, means a lighthouse is on the point (X, Y).

Output
How many pairs of lighthourses can beacon each other

( For every lighthouses, X coordinates wont be the same , Y coordinates wont be the same )

Example
Input

3
2 2
4 3
5 1
Output

1
Restrictions
For 90% test cases: 1 <= n <= 3 * 10^5

For 95% test cases: 1 <= n <= 10^6

For all test cases: 1 <= n <= 4 * 10^6

For every lighthouses, X coordinates wont be the same , Y coordinates wont be the same.

1 <= x, y <= 10^8

Time: 2 sec

Memory: 256 MB

Hints
The range of int is usually [-231, 231 - 1], it may be too small.

����
��������������Ϊ��·��ֻ������


https://dsa.cs.tsinghua.edu.cn/oj/attachment/c6c8/c6c8562b88ed7fd518cacf0264ae624f59598ed7.png
��ͼһ��

��ͼһ��ʾ��ÿ������������һյ̽�յƣ������䶫�������������Զ���ֱ������̽�յƵĹ���֮�����Ը����κξ��롣�������������֮С�����Լٶ����ǲ���˴��ڵ���


https://dsa.cs.tsinghua.edu.cn/oj/attachment/9d7f/9d7f16b4bddbee9795e12ba22fd7f88af5438aa6.png
��ͼ����

������A��B���ڶԷ���������Χ�ڣ���������ܹ������˴ˡ�������ͼ����ʵ���У�����������������˴ˣ������̵������ǣ��졢�̵���Ҳ���ǡ�

���ڣ������κ�һ������ĵ����������������ж��ٶԵ����ܹ������˴ˡ�

����
��n+1�С�

��1��Ϊ1������n����ʾ������������

��2��n+1��ÿ�а���2������x, y���ֱ��ʾ�������ĺᡢ�����ꡣ

���
1����������ʾ�������˴˵ĵ����Ե�������

����
��Ӣ������

����
����90%�Ĳ�����1 �� n �� 3��10^5

����95%�Ĳ�����1 �� n �� 10^6

ȫ��������1 �� n �� 4��10^6

����������x, y���������Ҳ�ͬ������x, y���������

1 �� x, y �� 10^8

ʱ�䣺2 sec

�ڴ棺256 MB

��ʾ
ע����������ͱ����ķ�Χ��C/C++�е�int����ͨ���������32λ�������䷶ΧΪ[-2^31, 2^31 - 1]����һ���㹻���ɱ���������


2018-8-7 22:56:34
����˼·
��������A(x1,y1),B(x2,y2)���Ա˴�����������Ϊ
1. (x1 < x2) && (y1 < y2)
2. (x1 > x2) && (y1 > y2)

��ô�������������갴X����󣬿ɼ�Ϊ����1

*/


#if !defined(_OJ_)
#define  _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif

#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>


//#include "list.h"

// Import from ProgramCaicai.
// http://www.xuetangx.com/courses/TsinghuaX/30240184X/2014_T2/discussion/forum/undefined/threads/54392f32459f089cdd008aa2
const int SZ = 1 << 10;
struct fastio
{
	char inbuf[SZ];
	char outbuf[SZ];
	fastio()
	{
		setvbuf(stdin, inbuf, _IOFBF, SZ);
		setvbuf(stdout, outbuf, _IOFBF, SZ);
	}
}io;
// Import end.

#define MAX_VER 4000000



//int Ligth[MAX_VER] = { 0 };

typedef struct LIGHT
{
	int x;
	int y;
	LIGHT(int a = 0, int b = 0) :x(a), y(b) {}
	LIGHT& operator=(const LIGHT& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
}LIGHT, *PLIGHT;

LIGHT Lights[MAX_VER] = { (0, 0) };
LIGHT LightsTemp[(MAX_VER >> 1) + 1] = { (0, 0) };
//list_node<PLIGHT> PosArray[MAX_VER] = { NULL };
//typedef List<LIGHT> LIGHT_LIST;
//typedef ListNode<LIGHT>* POS;

#ifndef max
#define max(a, b)	(a) > (b) ? (a) : (b) 
#endif

#ifndef min
#define min(a, b)	(a) < (b) ? (a) : (b) 
#endif

long long sum = 0;

void invertion_between(int lo, int mi, int hi)
{
#if !defined(_OJ_)
	char buff[128] = { 0 };
	sprintf(buff, "invertion_between lo %d mi %d hi %d\n", lo, mi, hi);
	OutputDebugStringA(buff);
#endif
	
	LIGHT *A = Lights + lo;
	int lb = mi - lo;
	LIGHT *B = LightsTemp; 
	for (int i = 0; i < lb; i++) { 
		B[i] = A[i]; 
	}
	int lc = hi - mi;
	LIGHT *C = Lights + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
		if ((j < lb) && (!(k < lc) || B[j].y <= C[k].y)) {
			if (k < lc) {
#if !defined(_OJ_)
				sprintf(buff, "sum++ B[%d].y %d, C[%d].y %d sum %lld, j+1 %d, lc-k %d, step %d\n",
						j, B[j].y, k, C[k].y, sum, j + 1, lc - k, (j + 1) * (lc - k));
				OutputDebugStringA(buff);
#endif
				sum += j + 1;
			}
			A[i++] = B[j++];
		}
		if ((k < lc) && (!(j < lb) || C[k].y < B[j].y)) {
			A[i++] = C[k++];
			sum++;
		}
	}

	//return sum;
}

void invertion_inside(int lo, int hi)
{
#if !defined(_OJ_)
	char buff[128] = { 0 };
	sprintf(buff, "invertion_inside lo %d hi %d\n", lo, hi);
	//OutputDebugStringA(buff);
#endif
	if (hi - lo < 2)
		return ;

	int mi = lo + ((hi - lo) >> 1);
	invertion_inside(lo, mi);
	invertion_inside(mi, hi);
	invertion_between(lo, mi, hi);
}

void merge(int lo, int mi, int hi)
{
#if !defined(_OJ_)
	char buff[128] = { 0 };
	sprintf(buff, "merge lo %d mi %d hi %d\n", lo, mi, hi);
	OutputDebugStringA(buff);
#endif

	LIGHT *A = Lights + lo;
	int lb = mi - lo;
	LIGHT *B = LightsTemp;
	for (int i = 0; i < lb; i++) {
		B[i] = A[i];
	}
	int lc = hi - mi;
	LIGHT *C = Lights + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
		if ((j < lb) && (!(k < lc) || B[j].x <= C[k].x)) {
			A[i++] = B[j++];
		}
		if ((k < lc) && (!(j < lb) || C[k].x < B[j].x))
			A[i++] = C[k++];
	}
}

void merge_sort(int lo, int hi)
{
#if !defined(_OJ_)
	char buff[128] = { 0 };
	sprintf(buff, "merge_sort lo %d hi %d\n", lo, hi);
	//OutputDebugStringA(buff);
#endif
	if (hi - lo < 2)
		return;

	int mi = lo + ((hi - lo) >> 1);
	merge_sort(lo, mi);
	merge_sort(mi, hi);
	merge(lo, mi, hi);
}

//inline int rand_int(int lo, int hi)
//{
//	return lo + rand() % (hi - lo);
//}

inline void swap(int a, int b)
{
	int x = Lights[a].x;
	int y = Lights[a].y;
	Lights[a].x = Lights[b].x;
	Lights[a].y = Lights[b].y;
	Lights[b].x = x;
	Lights[b].y = y;
}



void quik_sort(int lo, int hi)
{
#if !defined(_OJ_)
	char buff[128] = { 0 };
	sprintf(buff, "quik_sort lo %d hi %d\n", lo, hi);
	OutputDebugStringA(buff);
#endif
	if (lo >= hi)
		return;

	//swap(lo, rand_int(lo, hi));
	int mi = lo - 1;
	for (int i = lo; i < hi - 1; i++) {
		if (Lights[i].x <= Lights[hi - 1].x)
			swap(++mi, i);
	}

	swap(hi - 1, ++mi);
	quik_sort(lo, mi);
	quik_sort(mi + 1, hi);
}
//
//int Partition(int *A, int p, int r);
//void QuickSort(int *A, int p, int r) //��������  
//{
//	int q;
//	if (p<r)               //���p���ڵ���r ��ô�ͳ���ִ��  
//	{
//		q = Partition(A, p, r);  //���÷��η� �ҵ�q��ֵ  
//		QuickSort(A, p, q - 1);
//		QuickSort(A, q + 1, r);
//	}
//}
//
//int Partition(int *A, int p, int r) //���η������þ��ǽ������ΪA[p..q-1] ��A[q+1..r]  
//{                                                   //Ȼ�����Ԫ��ʹ��A[p..q-1]С�ڵ���q��ҲС�ڵ���A[q+1..r]  
//	int x, i, j, temp;
//
//	x = A[r];  //�����һ��ֵ������x��  
//	i = p - 1;   //��ʼ��ʱ��i �ƶ������������  
//	for (j = p; j <= r - 1; j++) {
//		if (A[j] <= x) {
//			i += 1;
//			temp = A[i]; //exchange  
//			A[i] = A[j];
//			A[j] = temp;
//		}
//	}
//
//	temp = A[i + 1];  //exchange  
//	A[i + 1] = A[r];
//	A[r] = temp;
//
//	return i + 1;  //����qֵ  
//}

//char bf[180 * 1024 * 1024] = { 0 };

int main_5(int argc, char* argv[])
{
	//int A[] = { 1, 2 };
	//QuickSort(A, 0, 1);
	//srand(static_cast<unsigned int>(time(NULL)));
	int n = 0;
	if (scanf("%d\n", &n) != 1)
		return 0;
	//LIGHT_LIST list;

	//int x = 0, y = 0;

	//fread(bf, 1, sizeof(bf), stdin);
	int pos = 0;
	for (int i = 0; i < n; i++) {
		//if (sscanf(bf + pos, "%d %d\n", &Lights[i].x, &Lights[i].y) != 2)
		//	return 0;
		/*while ((*(bf + pos++) != '\n')) {
			if (pos >= sizeof(bf))
				return 1;
		}*/
		//list.insert_as_last(LIGHT(x, y));
		//insert_and_sort_light(x, y);
		//Lights[i].x = x;
		//Lights[i].y = y;
		if (scanf("%d %d\n", &Lights[i].x, &Lights[i].y) != 2)
			return 0;
	}

	//list.sort();

//#ifndef _OJ_
//	ListNodePosi(LIGHT) p = list.first();
//	for (int i = 0; i < list.size(); i++, p = p->succ) {
//		printf("(%d, %d)\n", p->data.x, p->data.y);
//	}
//#endif
	//POS head = list.first();
	//quik_sort(0, n); 
	merge_sort(0, n);
	invertion_inside(0, n);
	printf("%lld\n", sum);
#if !defined(_OJ_)
	char buff[128] = { 0 };
	sprintf(buff, "total %lld\n", sum);
	OutputDebugStringA(buff);
#endif
	return 0;
}