#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main(int argc, char* argv[])
{
	int n;
	if (scanf("%d", &n) == EOF)
		return 0;

	int *A, *B, *C;
	A = new int[n];
	B = new int[n];
	C = new int[n];


	for (int i = 0; i < n; i++) {
		if (scanf("%d", &A[i]) == EOF)
			return 0;
	}

	for (int i = 0; i < n; i++) {
		if (scanf("%d", &B[i]) == EOF)
			return 0;
	}

	for (int i = 0; i < n; i++) {
		if (scanf("%d", &C[i]) == EOF)
			return 0;
	}

	int k;
	if (scanf("%d", &k) == EOF)
		return 0;

	struct MEMBER
	{
		bool chosen;
		MEMBER() :chosen(false) {}
	};

	MEMBER *members = new MEMBER[n+1];

	//int iA, iB, iC;
	//iA = iB = iC = 0;
	for (int iA = 0, iB = 0, iC = 0, i = 0, flag = 0; i < n; i++, flag = ++flag % 3) {
		if (flag == 0) {
			// a
			while (iA < n) {
				if (!members[A[iA]].chosen) {
					if (k == A[iA]) {
						printf("A\n");
						return 0;
					}
					members[A[iA]].chosen = true;
					break;
				} else {
					iA++;
				}
			}
		} else if (flag == 1) {
			// b
			while (iB < n) {
				if (!members[B[iB]].chosen) {
					if (k == B[iB]) {
						printf("B\n");
						return 0;
					}
					members[B[iB]].chosen = true;
					break;
				} else {
					iB++;
				}
			}
		} else {
			// c
			while (iC < n) {
				if (!members[C[iC]].chosen) {
					if (k == C[iC]) {
						printf("C\n");
						return 0;
					}
					members[C[iC]].chosen = true;
					break;
				} else {
					iC++;
				}
			}
		}
		
	}

	return 0;
}
