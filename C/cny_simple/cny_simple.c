/*
基础编程题目集 7-23 币值转换
分数 20
作者 陈建海
单位 浙江大学
输入一个整数（位数不超过9位）代表一个人民币值（单位为元），请转换成财务要求的大写中文格式。
如23108元，转换后变成“贰万叁仟壹百零捌”元。
为了简化输出，
用小写英文字母a-j顺序代表大写数字0-9，
用S、B、Q、W、Y分别代表拾、百、仟、万、亿。
于是23108元应被转换输出为“cWdQbBai”元。

输入格式：
输入在一行中给出一个不超过9位的非负整数。

输出格式：
在一行中输出转换后的结果。注意“零”的用法必须符合中文习惯。

输入样例1：
813227345
输出样例1：
iYbQdBcScWhQdBeSf
输入样例2：
6900
输出样例2：
gQjB
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char digits[10] = "abcdefghij";

void cny_under_1w(char* buf, int* plen, int n)
{
    int len = *plen;
    if (n / 1000) {
        buf[len++] = digits[n / 1000];
        buf[len++] = 'Q';
    } else {
        buf[len++] = digits[0];
    }
    n %= 1000;
    if (n / 100) {
        buf[len++] = digits[n / 100];
        buf[len++] = 'B';
    } else {
        buf[len++] = digits[0];
    }
    n %= 100;
    if (n / 10) {
        buf[len++] = digits[n / 10];
        buf[len++] = 'S';
    } else {
        buf[len++] = digits[0];
    }
    n %= 10;
    buf[len++] = digits[n];

    while (buf[len - 1] == 'a') {
        buf[len - 1] = '\0';
        len--;
    }
    *plen = len;
}

int main2()
{
    int n;
    scanf("%d", &n);
    char buf[128] = { 0 };
    int len = 0;
    if (n == 0) {
        buf[len++] = 'a';
        goto end;
    }

    if (n > 100000000) {
        buf[len++] = digits[n / 100000000];
        buf[len++] = 'Y';
        n %= 100000000;
    }

    if (n > 10000) {
        cny_under_1w(buf, &len, n / 10000);
        buf[len++] = 'W';
        n %= 10000;
    }

    cny_under_1w(buf, &len, n);

    // 移除开头的零
    char* next = buf;
    while (*next == 'a') {
        next++;
    }
    if (next != buf) {
        memmove(buf, next, strlen(next) + 1);
    }

    // 移除重复的零
    char* z = strchr(buf, 'a');
    while (z) {
        char* next = z + 1;
        char* pos = next;
        while (*next == 'a') {
            next++;
        }
        if (next != pos) {
            memmove(pos, next, strlen(next) + 1);
        }
        z = strchr(next, 'a');
    }

    // 移除拾后的零
    char* shi = strchr(buf, 'S');
    while (shi) {
        char* next = shi + 1;
        char* pos = next;
        if (*next == 'a') {
            next++;
            memmove(pos, next, strlen(next) + 1);
        }
        shi = strchr(next, 'S');
    }

end:
    printf("%s", buf);
}

int N;

int s[31]; // 存放划分结果 
int top = -1; // 数组指针 
int count = 0; // 统计输出的次数 
int sum = 0; // 拆分项累加和 

void division(int i);

int main()
{
    //scanf("%d", &N);
    N = 7;
    division(1);

    return 0;
}

void division(int i) {
    if (sum == N) {
        count++;
        printf("%d=", N);
        int k;
        for (k = 0; k < top; k++) {
            printf("%d+", s[k]);
        }
        if (count % 4 == 0 || s[top] == N) {
            printf("%d\n", s[top]);
        } else {
            printf("%d;", s[top]);
        }
        return;
    } // 输出部分 
    if (sum > N) {
        return;
    }
    for (int j = i; j <= N; j++) {
        s[++top] = j;
        sum += j;
        division(j);
        sum -= j;
        top--;
    } // 算法主体 
}