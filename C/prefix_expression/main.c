/*
https://pintia.cn/problem-sets/15/problems/836
7-21 求前缀表达式的值
分数 25
作者 DS课程组
单位 浙江大学
算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。
前缀表达式指二元运算符位于两个运算数之前，例如2+3*(7-4)+8/4的前缀表达式是：+ + 2 * 3 - 7 4 / 8 4。
请设计程序计算前缀表达式的结果值。

输入格式:
输入在一行内给出不超过30个字符的前缀表达式，只包含+、-、*、/以及运算数，不同对象（运算数、运算符号）之间以空格分隔。

输出格式:
输出前缀表达式的运算结果，保留小数点后1位，或错误信息ERROR。

输入样例:
+ + 2 * 3 - 7 4 / 8 4
输出样例:
13.0

代码长度限制16 KB
时间限制400 ms
内存限制64 MB
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