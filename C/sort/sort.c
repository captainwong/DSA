#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int* a, int lo, int hi)
{
	for (int last; lo < hi; hi = last) {
		for (int i = (last = lo) + 1; i < hi; i++) {
			if (a[i - 1] > a[i]) {
				int t = a[i - 1];
				a[i - 1] = a[i];
				a[i] = t;
				last = i;
			}
		}
	}
}

void insertionSort(int* a, int lo, int hi)
{
	if (hi - lo < 2)return;
	for (int i = lo + 1; i < hi; i++) {
		int cur = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > cur) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = cur;
	}
}

void selectionSort(int* a, int lo, int hi)
{
	while (lo < --hi) {
		int mx = hi;
		for (int i = hi; lo < i--; ) {
			if (a[i] > a[mx]) {
				mx = i;
			}
		}
		int t = a[hi];
		a[hi] = a[mx];
		a[mx] = t;
	}
}

void merge(int* a, int lo, int mi, int hi)
{
	int i = 0;
	int j = 0, lb = mi - lo;
	int k = 0, lc = hi - mi;
	int* A = a + lo;
	int* B = malloc(lb * sizeof(int));
	int* C = a + mi;
	for (int i = 0; i < lb; i++) {
		B[i] = A[i];
	}
	while (j < lb && k < lc) {
		A[i++] = B[j] <= C[k] ? B[j++] : C[k++];
	}
	while (j < lb) {
		A[i++] = B[j++];
	}
	free(B);
}

void mergeSort(int* a, int lo, int hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSort(a, lo, mi);
	mergeSort(a, mi, hi);
	merge(a, lo, mi, hi);
}

int partition(int* a, int lo, int hi)
{
	hi--;
	int pivot = a[lo];
	while (lo < hi) {
		while ((lo < hi) && pivot <= a[hi]) {
			hi--;
		}
		a[lo] = a[hi];
		while ((lo < hi) && a[lo] <= pivot) {
			lo++;
		}
		a[hi] = a[lo];
	}
	a[lo] = pivot;
	return lo;
}

void quickSort(int* a, int lo, int hi)
{
	if (hi - lo < 2)return;
	int mi = partition(a, lo, hi);
	quickSort(a, lo, mi);
	quickSort(a, mi + 1, hi);
}

void test(char* name, void(*sort)(int*, int, int))
{
	printf("Testing %s\n", name);
	int a[7] = { 5,2,7,4,6,3,1 };
	printf("before sorting, A=\n[");
	for (int i = 0; i < 7; i++) {
		printf("%s%d", i == 0 ? "" : ", ", a[i]);
	}
	sort(a, 0, 7);
	printf("]\nafter sorted, A=\n[");
	for (int i = 0; i < 7; i++) {
		printf("%s%d", i == 0 ? "" : ", ", a[i]);
	}
	printf("]\n\n");
}

#define TEST(sort) test(#sort, sort)

int main()
{
	TEST(bubbleSort);
	TEST(insertionSort);
	TEST(selectionSort);
	TEST(mergeSort);
	TEST(quickSort);
}