// quick_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

int partition(int* A, int p, int r)
{
	printf("partitioning... A[p] %d A[r] %d, p %d r %d\n", A[p], A[r], p, r);
	int x = A[r];
	printf("pivot x is A[r] %d, r %d\n", x, r);
	int i = p - 1;
	printf("for start\n");
	for (int j = p; j < r; j++) {
		printf("\tforring: j %d, i %d\n", j, i);
		printf("\tcomparing between A[%d] %d and x %d\n", j, A[j], x);
		if (A[j] <= x) {
			printf("\t\tif(A[j] <= x) is true. j %d, A[j] %d <= x %d\n", j, A[j], x);
			i++;
			printf("\t\ti++ %d\n", i);
			printf("\t\tswaping A[i] %d and A[j] %d\n", A[i], A[j]);
			swap(A[i], A[j]);
			printf("\t\tswapped A[i] %d and A[j] %d\n", A[i], A[j]);
		} else {
			printf("\t\tif(A[j] <= x) is false. j %d, A[j] %d <= x %d\n", j, A[j], x);
		}
	}
	printf("for end\n");
	printf("swaping A[i+1] %d and A[r] %d, i %d, r %d\n", A[i + 1], A[r], i, r);
	swap(A[i + 1], A[r]);
	printf("partition end:\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	printf("partition end, pivot is %d\n", i + 1);
	return i + 1;
}

void qsort(int* A, int p, int r)
{
	printf("before sort:\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	if (p < r) {
		int q = partition(A, p, r);
		qsort(A, p, q - 1);
		qsort(A, q + 1, r);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	int A[] = { 2, 8, 7, 1, 3, 5, 6, 4 };
	qsort(A, 0, 7);
	return 0;
}

