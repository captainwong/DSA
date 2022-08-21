#include "bst.h"
#ifdef _MSC_VER // 当前编译器是否为 Visual Studio
#define _CRT_SECURE_NO_WARNINGS // 只有在 Visual Studio 下才需要定义此宏
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int D[101][101] = { 0 };
int A[101] = { 0 };
int B[101] = { 0 };

int callatz(int n)
{
    if (n % 2 == 0) {
        return n / 2;
    } else {
        return (3 * n + 1) / 2;
    }
}

int main()
{
    int K, a = 0, b = 0;
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        scanf("%d", &A[a++]);
    }

    for (int i = 0; i < a; i++) {
        int c = A[i];
        while (c != 1) {
            if (D[A[i]][c] == 0) {
                D[A[i]][c] = 1;
            }
            c = callatz(c);
        }
    }

    for (int i = 0; i < a; i++) {
        int ok = 1;
        int n = A[i];
        for (int j = 0; j < a; j++) {
            int m = A[j];
            if (!D[n][m]) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            B[b++] = A[i];
        }
    }

    for (int i = b - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (B[j] > B[j + 1]) {
                int t = B[j];
                B[j] = B[j + 1];
                B[j + 1] = t;
            }
        }
    }

    for (int i = b - 1; i >= 0; i--) {
        printf("%s%d", i == b - 1 ? "" : " ", B[i]);
    }
}