/*
���������Ŀ�� 7-23 ��ֵת��
���� 20
���� �½���
��λ �㽭��ѧ
����һ��������λ��������9λ������һ�������ֵ����λΪԪ������ת���ɲ���Ҫ��Ĵ�д���ĸ�ʽ��
��23108Ԫ��ת�����ɡ�������ǪҼ����ơ�Ԫ��
Ϊ�˼������
��СдӢ����ĸa-j˳������д����0-9��
��S��B��Q��W��Y�ֱ����ʰ���١�Ǫ�����ڡ�
����23108ԪӦ��ת�����Ϊ��cWdQbBai��Ԫ��

�����ʽ��
������һ���и���һ��������9λ�ķǸ�������

�����ʽ��
��һ�������ת����Ľ����ע�⡰�㡱���÷������������ϰ�ߡ�

��������1��
813227345
�������1��
iYbQdBcScWhQdBeSf
��������2��
6900
�������2��
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

    // �Ƴ���ͷ����
    char* next = buf;
    while (*next == 'a') {
        next++;
    }
    if (next != buf) {
        memmove(buf, next, strlen(next) + 1);
    }

    // �Ƴ��ظ�����
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

    // �Ƴ�ʰ�����
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

int s[31]; // ��Ż��ֽ�� 
int top = -1; // ����ָ�� 
int count = 0; // ͳ������Ĵ��� 
int sum = 0; // ������ۼӺ� 

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
    } // ������� 
    if (sum > N) {
        return;
    }
    for (int j = i; j <= N; j++) {
        s[++top] = j;
        sum += j;
        division(j);
        sum -= j;
        top--;
    } // �㷨���� 
}