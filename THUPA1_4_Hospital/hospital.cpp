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

	//VILLAGE* v = new VILLAGE[n + 1];
	//longlong *Ewd = new longlong[n + 1];
	longlong EWD_zero = 0;
	longlong Ewn = 0;
	//Ewd[0] = 0;
	longlong v[32768] = { 0 };
	//v[0].x = v[0].w = 0;
	int x, w;
	int minimize_index = 32768;
	for (int i = 0; i < n; i++) {
		if (scanf("%d %d", &x, &w) == EOF)
			return 0;
		minimize_index = minimize_index < x ? minimize_index : x;
		//if (v[x] < w)
			v[x] += w;
		EWD_zero += (longlong)x * (longlong)w;
		//EwdN += wd[i];
		Ewn += w;
	}

#ifndef _OJ_
	//print_vellage(v, 1, n + 1);
#endif

	//quik_sort(v, 1, n);

#ifndef _OJ_
	//print_vellage(v, 1, n + 1);
#endif

	longlong Ewd_first = 0;
	if (minimize_index == 0) {
		Ewd_first = EWD_zero;
	} else {
		Ewd_first = EWD_zero - minimize_index * Ewn;
	}
	
	int prev_index = minimize_index;
	longlong prev_ewdn = Ewd_first;
	longlong minimize_ewdn = Ewd_first;
	longlong Ewn_prev = v[minimize_index];
	for (int i = minimize_index + 1; i < 32768; i++) {
		if (v[i] != 0) {
			longlong ewdi = prev_ewdn + 2 * (i - prev_index) * Ewn_prev
				+ (prev_index - i) * Ewn;
			prev_ewdn = ewdi;
			Ewn_prev += v[i];
			if (ewdi < minimize_ewdn) {
				minimize_index = i;
				minimize_ewdn = ewdi;
			}
			prev_index = i;
		}
		//longlong Ewdi = abs(EwdN - static_cast<longlong>(vellages[i].x) * EWn - 2 * Ewd[i - 1]);
		// Ewn is exactly the prev Ewn
		
	}
	printf("%d\n", minimize_index);
	printf("%lld\n", minimize_ewdn);

	return 0;
}