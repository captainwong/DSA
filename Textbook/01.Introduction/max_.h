#pragma once 


// 从数组区间A[lo, hi)中找出最大的两个整数A[x1]和A[x2]	// A[x1] >= A[x2]
// 元素比较的次数，要求尽可能地少
void max2_iter1(int A[], int lo, int hi, int& x1, int & x2)	// 1 < n = hi - lo
{
	x1 = lo;
	for (int i = lo + 1; i < hi; i++) {	// 扫描A[lo, hi)，找出A[x1]
		if (A[x1] < A[i]) {
			x1 = i;	// hi - lo - 1 = n - 1
		}
	}

	x2 = lo;
	for (int i = lo + 1; i < x1; i++) {	// 扫描A[lo, x1]
		if (A[x2] < A[i]) {
			x2 = i;	// x1 - lo - 1
		}
	}

	for (int i = x1 + 1; i < hi; i++) {	// 扫描A(x1, hi)，找出A[x2]
		if (A[x2] < A[i]) {
			x2 = i;	// hi - x1 - 1
		}
	}

	// Total time is always 2n-3
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}


void max2_iter2(int A[], int lo, int hi, int& x1, int& x2)
{
	if (A[x1 = lo] < A[x2 = lo + 1]) {
		swap(x1, x2);	// 1
	}

	for (int i = lo + 2; i < hi; i++) {
		if (A[x2] < A[i]) {
			if (A[x1] < A[x2 = i]) {
				swap(x1, x2);
			}
		}
	}

	// Best case: 1 + (n-2)*1 = n - 1
	// Worst case: 1 + (n-2)*2 = 2n -3
}


void max2_recursive(int A[], int lo, int hi, int& x1, int& x2)
{
	if (lo + 2 == hi) {
		if (A[x1 = lo] < A[x2 = lo + 1]) {
			swap(x1, x2);
		}
		return;
	}

	if (lo + 3 == hi) {
		max2_iter2(A, lo, hi, x1, x2);
		return;
	}

	int mi = (lo + hi) >> 1;
	int x1L, x2L;
	max2_recursive(A, lo, mi, x1L, x2L);
	int x1R, x2R;
	max2_recursive(A, mi, hi, x1R, x2R);

	if (A[x1L > A[x1R]]) {
		x1 = x1L;
		x2 = A[x2L] > A[x1R] ? x2L : x1R;
	} else {
		x1 = x1R;
		x2 = A[x2R] > A[x1L] ? x2R : x1L;
	}
}