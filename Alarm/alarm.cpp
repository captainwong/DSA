#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#ifndef _OJ_
#include <time.h>
#endif

typedef struct _PA
{
	int x;
	int y;
}Point, Alarm;

// P(px, py) on which side of Vecter AB, A(xa, 0), B(0, yb)
// + right
// 0 on
// - left
inline int getSide(int xa, int yb, int px, int py)
{
	long long ret = ((long long)px * (long long)py - (long long)(xa - px) * (long long)(yb - py));
	if (ret > 0) {
		return 1;
	} else if (ret == 0) {
		return 0;
	} else {
		return -1;
	}
}

enum Side
{
	LEFT,
	RIGHT,
};

int searchSide(Point* A, int n, int m, int x, int y, Side side)
{
	if (side == RIGHT) {
		int mm = m + ((n - m) >> 1);
		int prev_mm = m;
		int ret = 0;
		while ((ret = getSide(A[mm].x, A[mm].y, x, y)) > 0) {
			if (mm == n - 1) {
				return mm;
			} else {
				prev_mm = mm;
				mm += (n - mm) >> 1;
			}
		}

		/*while ((ret = getSide(A[mm].x, A[mm].y, x, y)) < 0) {
			mm = prev_mm + ((mm - prev_mm) >> 1);
		}*/

		do {
			if (ret == 0) {
				return mm;
			} else if (ret < 0) {
				mm--;
				ret = getSide(A[mm].x, A[mm].y, x, y);
			} else {
				return mm;
			}
		} while (mm > 0);
	} else {
		int mm = m >> 1;
		int prev_mm = m;
		int ret = 0;
		while ((ret = getSide(A[mm].x, A[mm].y, x, y)) < 0) {
			if (mm == 1) {
				return 0;
			} else {
				prev_mm = mm;
				mm = mm >> 1;
			}
		}

		/*while (mm > 0 && (ret = getSide(A[mm].x, A[mm].y, x, y)) > 0) {
			mm = mm >> 1;
		}*/

		do {
			if (ret == 0) {
				return mm;
			} else if (ret > 0) {
				mm++;
				ret = getSide(A[mm].x, A[mm].y, x, y);
			} else {
				return mm - 1;
			}
		} while (mm < n);
	}
	return 0;
}

int getRange(Point* A, int n, int x, int y)
{
	if (x == 0 && y == 0)
		return 0;

	int m = n >> 1;
	int side = getSide(A[m].x, A[m].y, x, y);
	if (side == 0) {		
		// on
		return m;
	} else if (side > 0) {	
		// right
		return searchSide(A, n, m, x, y, RIGHT);
	} else {				
		// left
		return searchSide(A, n, m, x, y, LEFT);
	}
}

int g_range = 1;

int getRange2(Alarm* A, int n, int x, int y)
{
	if (x == 0 && y == 0)
		return 0;

	int range = g_range;
	int mm = 1;
	int side = getSide(A[mm].x, A[mm].y, x, y);

	while (0 < side && mm < n) {
		while (mm + range >= n && range >= 10) {
			range /= 10;
		}
		mm += range;
		side = getSide(A[mm].x, A[mm].y, x, y);
	}

	if (side == 0) {
		return mm;
	} else if (range == 1) {
		return mm - 1;
	}
	
	while (side < 0 && 1 < mm) {
		while (mm > range && range >= 10) {
			range /= 10;
		}
		mm -= range;
		side = getSide(A[mm].x, A[mm].y, x, y);
	}

	if (side == 0) {
		return mm;
	} else if (range == 1) {
		return mm + 1;
	}

	while (0 < side && mm < n) {
		mm++;
		side = getSide(A[mm].x, A[mm].y, x, y);
	}

	return mm;
}

int main(int /*argc*/, char* /*argv[]*/)
{
#ifndef _OJ_
	clock_t start, stop;
	start = clock();
#endif
	int n, m;
	if (scanf("%d %d\n", &n, &m) == EOF)
		return 1;

	if (n < 100) {
		g_range = 1;
	} else {
		g_range = n / 10;
	} /*if (n < 1000) {
		g_range = 10;
	} else if (n < 10000) {
		g_range = 100;
	} else if (n < 100000) {
		g_range = 1000;
	} else {
		g_range = 10000;
	}*/

	Alarm *alarm = new Alarm[n + 1];
	for (int i = 1; i <= n; i++) {
		if (scanf("%d %d\n", &alarm[i].x, &alarm[i].y) == EOF)
			return 1;
	}

	int x, y;
	for (int i = 0; i < m; i++) {
		if (scanf("%d %d\n", &x, &y) == EOF)
			return 1;

		printf("%d\n", getRange2(alarm, n + 1, x, y));
	}
#ifndef _OJ_
	stop = clock();
	printf("%6.3f\n", stop - start);
#endif
	return 0;
}
