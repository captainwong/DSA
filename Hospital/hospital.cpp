#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long longlong;

struct VILLAGE
{
	int x;
	int w;
};

int rand_int(int lo, int hi)
{
	int ret = 0;
	while (ret < lo) {
		ret = rand() % hi;
	}
	return ret;
}

inline void swap(VILLAGE* V, int a, int b)
{
	int x = V[a].x;
	int w = V[a].w;
	V[a].x = V[b].x;
	V[a].w = V[b].w;
	V[b].x = x;
	V[b].w = w;
}

void quik_sort(VILLAGE* V, int lo, int hi)
{
	if (lo >= hi)
		return;

	swap(V, lo, rand_int(lo, hi));
	int mi = lo;
	for (int i = lo + 1; i <= hi; i++) {
		if (V[i].x < V[lo].x)
			swap(V, ++mi, i);
	}

	swap(V, lo, mi);
	quik_sort(V, lo, mi - 1);
	quik_sort(V, mi + 1, hi);
}

#ifndef _OJ_
void print_vellage(VILLAGE* V, int lo, int hi)
{
	while (lo < hi) {
		printf("#%d (%d,%d)\n", lo, V[lo].x, V[lo].w);
		lo++;
	}
}
#endif

//longlong abs(longlong v)
//{
//	return v >= 0 ? v : -v;
//}

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(NULL)));
	int n;
	if (scanf("%d", &n) == EOF)
		return 0;

	VILLAGE* v = new VILLAGE[n + 1];
	//longlong *Ewd = new longlong[n + 1];
	longlong Ewd0 = 0;
	longlong Ewn = 0;
	//Ewd[0] = 0;
	v[0].x = v[0].w = 0;
	for (int i = 1; i <= n; i++) {
		if (scanf("%d %d", &v[i].x, &v[i].w) == EOF)
			return 0;
		Ewd0 += (longlong)v[i].x * (longlong)v[i].w;
		//EwdN += wd[i];
		Ewn += v[i].w;
	}

#ifndef _OJ_
	print_vellage(v, 1, n + 1);
#endif

	quik_sort(v, 1, n);

#ifndef _OJ_
	print_vellage(v, 1, n + 1);
#endif

	longlong Ewd1 = Ewd0 - v[1].x * Ewn;
	int minimize_index = 1;
	longlong prev_ewdn = Ewd1;
	longlong minimize_ewdn = Ewd1;
	longlong Ewn_prev = v[1].w;
	for (int i = 2; i <= n; i++) {
		//longlong Ewdi = abs(EwdN - static_cast<longlong>(vellages[i].x) * EWn - 2 * Ewd[i - 1]);
		// Ewn is exactly the prev Ewn
		longlong ewdi = prev_ewdn + 2 * (v[i].x - v[i - 1].x) * Ewn_prev 
			+ (v[i - 1].x - v[i].x) * Ewn;
		prev_ewdn = ewdi;
		Ewn_prev += v[i].w;
		if (ewdi < minimize_ewdn) {
			minimize_index = i;
			minimize_ewdn = ewdi;
		}
	}
	printf("%d\n", v[minimize_index].x);
	printf("%lld\n", minimize_ewdn);

	return 0;
}