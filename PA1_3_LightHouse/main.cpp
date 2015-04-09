#if !defined(_OJ_)
#define  _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//#include "list.h"

// Import from ProgramCaicai.
// http://www.xuetangx.com/courses/TsinghuaX/30240184X/2014_T2/discussion/forum/undefined/threads/54392f32459f089cdd008aa2
const int SZ = 1 << 20;
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

	bool operator <= (const LIGHT& rhs)
	{
		return x <= rhs.x;
	}



}LIGHT, *PLIGHT;

LIGHT Lights[MAX_VER] = { (0, 0) };
LIGHT LightsTemp[MAX_VER] = { (0, 0) };
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
				sum +=  (lc - k);
			}
			A[i++] = B[j++];
		}
		if ((k < lc) && (!(j < lb) || C[k].y < B[j].y))
			A[i++] = C[k++];
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


inline int rand_int(int lo, int hi)
{
	return lo + rand() % (hi - lo);
}

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

	swap(lo, rand_int(lo, hi));
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
//void QuickSort(int *A, int p, int r) //快速排序  
//{
//	int q;
//	if (p<r)               //如果p大于等于r 那么就程序不执行  
//	{
//		q = Partition(A, p, r);  //调用分治法 找到q的值  
//		QuickSort(A, p, q - 1);
//		QuickSort(A, q + 1, r);
//	}
//}
//
//int Partition(int *A, int p, int r) //分治法，作用就是将数组分为A[p..q-1] 和A[q+1..r]  
//{                                                   //然后调整元素使得A[p..q-1]小于等于q，也小于等于A[q+1..r]  
//	int x, i, j, temp;
//
//	x = A[r];  //将最后一个值保存在x中  
//	i = p - 1;   //开始的时候将i 移动到数组的外面  
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
//	return i + 1;  //返回q值  
//}


int main(int argc, char* argv[])
{
	//int A[] = { 1, 2 };
	//QuickSort(A, 0, 1);
	srand(static_cast<unsigned int>(time(NULL)));
	int n = 0;
	if (scanf("%d", &n) == EOF)
		return 0;
	//LIGHT_LIST list;

	//int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		if (scanf("%d %d", &Lights[i].x, &Lights[i].y) == EOF)
			return 0;
		//list.insert_as_last(LIGHT(x, y));
		//insert_and_sort_light(x, y);
		//Lights[i].x = x;
		//Lights[i].y = y;
	}

	//list.sort();

//#ifndef _OJ_
//	ListNodePosi(LIGHT) p = list.first();
//	for (int i = 0; i < list.size(); i++, p = p->succ) {
//		printf("(%d, %d)\n", p->data.x, p->data.y);
//	}
//#endif
	//POS head = list.first();
	quik_sort(0, n );
	invertion_inside(0, n);
	printf("%lld\n", sum);
#if !defined(_OJ_)
	char buff[128] = { 0 };
	sprintf(buff, "total %lld\n", sum);
	OutputDebugStringA(buff);
#endif
	return 0;
}