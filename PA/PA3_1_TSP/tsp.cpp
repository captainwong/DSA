#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "../../include/graph_matrix.h"

int main(int /*argc*/, char** /*argv*/)
{
	int n, m;
	if (scanf("%d %d\n", &n, &m) == EOF)
		return 1;



	int a, b;
	for (int i = 0; i < m; i++) {
		if (scanf("%d %d", &a, &b) == EOF)
			return 1;

	}
	return 0;
}

