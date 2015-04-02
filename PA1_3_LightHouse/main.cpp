#define  _CRT_SECURE_NO_WARNINGS
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
	/*LIGHT& operator=(const LIGHT& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}*/

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

#define max(a, b)	(a) > (b) ? (a) : (b) 
#define min(a, b)	(a) < (b) ? (a) : (b) 


long long invertion_between(int lo, int mi, int hi)
{
	long long sum = 0;
	LIGHT *A = Lights + lo;
	int lb = mi - lo;
	LIGHT *B = LightsTemp; for (int i = 0; i < lb; i++) { B[i] = A[i]; }
	int lc = hi - mi;
	LIGHT *C = A + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
		if ((j < lb) && (lc <= k || B[j].y < C[k].y)) {
			if (k < lc && (B[j].y < C[k].y)) {
				sum += lc - k;
			}
			A[i++] = B[j++];
		}
		if ((k < lc) && (lb <= j || C[k].y < B[j].y))
			A[i++] = C[k++];
	}

	return sum;
}

long long invertion_inside(int lo, int hi)
{
	if (hi == lo)
		return 0;

	int mi = (hi + lo) >> 1;
	long long l = invertion_inside(lo, mi);
	long long r = invertion_inside(mi + 1, hi);
	return l + r + invertion_between(lo, mi, hi);
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
	if (lo >= hi)
		return;

	swap(lo, rand_int(lo, hi));
	int mi = lo;
	for (int i = lo + 1; i < hi; i++) {
		if (Lights[i].x < Lights[lo].x)
			swap(++mi, i);
	}

	swap(lo, mi);
	quik_sort(lo, mi - 1);
	quik_sort(mi + 1, hi);
}


int main(int argc, char* argv[])
{
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
	quik_sort(0, n);
	long long total = invertion_inside(0, n);
	printf("%lld\n", total);
	return 0;
}