#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

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


struct LIGHT
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

};

typedef List<LIGHT> LIGHT_LIST;
typedef ListNode<LIGHT>* POS;

#define max(a, b)	{ (a) > (b) ? (a) : (b) }


long long invertion_between(LIGHT_LIST& L, POS& pL, int n, POS pR, int m)
{
	POS pp = pL->pred;
	long long sum = 0;
	while (0 < m) {
		if ((0 < n) && (pL->data.y < pR->data.y)) {
			sum += m;
			if (pR == (pL = pL->succ))
				break;
			n--;
		} else {
			L.insert_before(pL, L.remove((pR = pR->succ)->pred));
			m--;			
		}
	}
	pL = pp->succ;
	return sum;
}

long long invertion_inside(LIGHT_LIST& L, POS& p, int n)
{
	if (n < 2)
		return 0;

	int mi = n >> 1;
	POS q = p;
	for (int i = 0; i < mi; i++) {
		q = q->succ;
	}
	long long l = invertion_inside(L, p, mi);
	long long r = invertion_inside(L, q, n - mi);
	return l + r + invertion_between(L, p, mi, q, n - mi);
}

int main(int argc, char* argv[])
{
	int n = 0;
	if (scanf("%d", &n) == EOF)
		return 0;

	LIGHT_LIST list;

	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		if (scanf("%d %d", &x, &y) == EOF)
			return 0;
		list.insert_as_last(LIGHT(x, y));
	}

	list.sort();

//#ifndef _OJ_
//	ListNodePosi(LIGHT) p = list.first();
//	for (int i = 0; i < list.size(); i++, p = p->succ) {
//		printf("(%d, %d)\n", p->data.x, p->data.y);
//	}
//#endif
	POS head = list.first();
	long long total = invertion_inside(list, head, list.size());
	printf("%lld\n", total);
	return 0;
}