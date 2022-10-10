#include <stdio.h>
#include <math.h>

void gou_gu(int n)
{
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			double k = sqrt(i * i + j * j);
			if (k == (int)k) {
				printf("%d %d %d\n", i, j, (int)k);
			}
		}
	}
}

int main()
{
	gou_gu(100);
}
