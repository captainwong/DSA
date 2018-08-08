#pragma once

int lcs_recursive(char A[], int m, char B[], int n)
{
	static char a[128] = { 0 };
	static char b[128] = { 0 };
	strncpy_s(a, A, m + 1);
	strncpy_s(b, B, n + 1);
	static char out[128] = { 0 };
	sprintf_s(out, "call: A %s, m %d, B %s, n %d\n", a, m, b, n);
	OutputDebugString(out);
	if (m < 0 || n < 0) {
		sprintf_s(out, "return 0, m %d, n %d\n", m, n);
		OutputDebugString(out);
		return 0;
	}

	if (A[m] == B[n]) {
		int ret = lcs_recursive(A, m - 1, B, n - 1) + 1;
		sprintf_s(out, "return: %d, m %d, n %d\n", ret, m, n);
		OutputDebugString(out);
		return ret;
	} else {
		int r1 = lcs_recursive(A, m, B, n - 1); 
		int r2 = lcs_recursive(A, m - 1, B, n);
		int ret = r1 > r2 ? r1 : r2;
		sprintf_s(out, "return: %d, m %d, n %d\n", ret, m, n);
		OutputDebugString(out);
		return ret;
	}
}