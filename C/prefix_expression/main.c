/*
https://pintia.cn/problem-sets/15/problems/836
7-21 ��ǰ׺���ʽ��ֵ
���� 25
���� DS�γ���
��λ �㽭��ѧ
�������ʽ��ǰ׺��ʾ������׺��ʾ���ͺ�׺��ʾ������ʽ��
ǰ׺���ʽָ��Ԫ�����λ������������֮ǰ������2+3*(7-4)+8/4��ǰ׺���ʽ�ǣ�+ + 2 * 3 - 7 4 / 8 4��
����Ƴ������ǰ׺���ʽ�Ľ��ֵ��

�����ʽ:
������һ���ڸ���������30���ַ���ǰ׺���ʽ��ֻ����+��-��*��/�Լ�����������ͬ������������������ţ�֮���Կո�ָ���

�����ʽ:
���ǰ׺���ʽ��������������С�����1λ���������ϢERROR��

��������:
+ + 2 * 3 - 7 4 / 8 4
�������:
13.0

���볤������16 KB
ʱ������400 ms
�ڴ�����64 MB
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Item {
    int isop;
    double val;
    char op;
}Item;

void readExpr(char* s)
{
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n')break;
        *s++ = c;
    }
    *s = '\0';
}

int readDigit(char** s, double* D)
{
    int negative = 0;
    if (**s == '+' || **s == '-') {
        if (**s == '-') {
            negative = 1;
        }
        (*s)++;
    }
    if (!isdigit(**s)) {
        return 0;
    }
    double val = **s - '0';
    while (isdigit(*(++ * s))) {
        val = val * 10 + **s - '0';
    }
    if (**s != '.') {
        *D = negative ? -val : val;
        return 1;
    }
    (*s)++;
    double fraction = 0.1;
    if (!isdigit(**s)) {
        return 0;
    }
    while (isdigit(**s)) {
        val += (*(*s)++ - '0') * fraction;
        fraction *= 0.1;
    }
    *D = negative ? -val : val;
    return 1;
}

int readItems(Item* items, int*N)
{
    char expr[32];
    readExpr(expr);
    char* s = expr;
    int n = 0;

    while (*s) {
        if (isdigit(*s) || ((*s == '+' || *s == '-') && *(s + 1) && isdigit(*(s + 1)))) {
            items[n].isop = 0;
            if (!readDigit(&s, &items[n].val)) {
                return 0;
            }
            n++;
        } else if (*s == ' ') {
            s++;
        } else {
            items[n].isop = 1;
            items[n].op = *s++;
            n++;
        }
    }
    *N = n;
    return 1;
}

double calc(double a, double b, char op)
{
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': 
        if (b == 0) {
            puts("ERROR"); exit(0);
        }
        return a / b;
    }
    return 0;
}

int main()
{
    Item s[32];
    int sn;
    if (!readItems(s, &sn)) {
        puts("ERROR");
        return 0;
    }
    Item t[32];
    int n = 0;
    for (int i = 0; i < sn; i++) {
        t[n++] = s[i];
        while (n >= 3 && !t[n - 1].isop && !t[n - 2].isop && t[n - 3].isop) {
            t[n - 3].isop = 0;
            t[n - 3].val = calc(t[n - 2].val, t[n - 1].val, t[n - 3].op);
            n-=2;
        }
    }
    if (n != 1) {
        puts("ERROR");
    } else {
        printf("%.1lf", t[0].val);
    }

    
}