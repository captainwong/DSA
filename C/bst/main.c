#include "bst.h"
#ifdef _MSC_VER // 当前编译器是否为 Visual Studio
#define _CRT_SECURE_NO_WARNINGS // 只有在 Visual Studio 下才需要定义此宏
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include<stdio.h>
#include<string.h>
#include <math.h>
//
//int partition(int* a, int lo, int hi) 
//{
//    int pivot = a[lo];
//    hi--;
//    while (lo < hi) {
//        while ((lo < hi) && (pivot <= a[hi])) {
//            hi--;
//        }
//        a[lo] = a[hi];
//        while ((lo < hi) && (a[lo] <= pivot)) {
//            lo++;
//        }
//        a[hi] = a[lo];
//    }
//    a[lo] = pivot;
//    return lo;
//}
//
//void quick_sort(int* a, int lo, int hi)
//{
//    if (hi - lo < 2)return;
//    int m = partition(a, lo, hi);
//    quick_sort(a, 0, m);
//    quick_sort(a, m + 1, hi);
//}
//
//int main()
//{
//    int n, m;
//    scanf("%d %d", &n, &m);
//    int* a = malloc(n * sizeof(int));
//    for (int i = 0; i < n; i++) {
//        scanf("%d", &a[i]);
//    }
//    quick_sort(a, 0, n - 1);
//    int* b = malloc(m * sizeof(int));
//    for (int i = 0; i < m; i++) {
//        scanf("%d", &b[i]);
//    }
//    quick_sort(b, 0, m - 1);
//    int k = 0;
//    for (int i = 0, j = 0; i < n && j < m; ) {
//        if (a[i] < b[j]) {
//            i++;
//        } else if (a[i] > b[j]) {
//            j++;
//        } else {
//            i++; j++; k++;
//        }
//    }
//    printf("%d ", k);
//    return 0;
//}

#include <stdlib.h>

char* readline()
{
    int C = 16, n = 0, c;
    char* s = malloc(C);
    while ((c = getchar()) != EOF) {
        if (c == '\n')break;
        s[n++] = c;
        if (n == C - 1) {
            C <<= 2;
            char* t = malloc(C);
            memcpy(t, s, n);
            free(s);
            s = t;
        }
    }
    s[n] = '\0';
    return s;
}

char* readtill(char e)
{
    int C = 16, n = 0, c;
    char* s = malloc(C);
    while ((c = getchar()) != EOF) {
        if (c == e)break;
        s[n++] = c;
        if (n == C - 1) {
            C <<= 2;
            char* t = malloc(C);
            memcpy(t, s, n);
            free(s);
            s = t;
        }
    }
    s[n] = '\0';
    return s;
}

char* readlinen(int*N)
{
    int C = 16, n = 0, c;
    char* s = malloc(C);
    while ((c = getchar()) != EOF) {
        if (c == '\n')break;
        s[n++] = c;
        if (n == C - 1) {
            C <<= 2;
            char* t = malloc(C);
            memcpy(t, s, n);
            free(s);
            s = t;
        }
    }
    s[n] = '\0';
    *N = n;
    return s;
}

int readline_static(char* s, int len)
{
    int c,n=0;
    while ((c = getchar()) != EOF && n < len - 1) {
        if (c == '\n')break;
        s[n++] = c;
    }
    s[n] = '\0';
    return n;
}
#include<stdio.h>
#include<string.h>
#include <stdlib.h>


typedef struct Student {
    char* name;
    int grade;
}Student;

Student students[10000];

int cmp(Student a, Student b)
{
    if (a.grade > b.grade) {
        return -1;
    } else if (a.grade < b.grade) {
        return 1;
    } else {
        return strcmp(b.name, a.name);
    }
}

int partition(Student* a, int lo, int hi)
{
    hi--;
    Student pivot = a[lo];
    while (lo < hi) {
        while ((lo < hi) && cmp(pivot, a[hi]) <= 0) {
            hi--;
        }
        a[lo] = a[hi];
        while ((lo < hi) && cmp(a[lo], pivot) <= 0) {
            lo++;
        }
        a[hi] = a[lo];
    }
    a[lo] = pivot;
    return lo;
}

void quick_sort(Student* a, int lo, int hi)
{
    if (hi - lo < 2) return;
    int m = partition(a, lo, hi);
    quick_sort(a, lo, m);
    quick_sort(a, m + 1, hi);
}

int main()
{
    int n; scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        students[i].name = readtill(' ');
        scanf("%d\n", &students[i].grade);
    }
    quick_sort(students, 0, n);
    for (int i = 0; i < n; i++) {
        puts(students[i].name);
    }
    return 0;
}