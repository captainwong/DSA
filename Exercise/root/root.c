/*
https://pintia.cn/problem-sets/14/problems/798
���������Ŀ�� 7-18 ���ַ������ʽ����
���� 20
���� ����
��λ ������ѧԺ
���ַ���������ԭ��Ϊ�������������f(x)������[a,b]�������˵�ȡֵ��ţ���f(a)f(b)<0��
������������������ٴ���1����r����f(r)=0��

���ַ��Ĳ���Ϊ��

������䳤�ȣ����С�ڸ�����ֵ����ֹͣ����������е�(a+b)/2������
���f(a)f(b)<0��������е��ֵf((a+b)/2)��
���f((a+b)/2)����Ϊ0����(a+b)/2����Ҫ��ĸ�������
���f((a+b)/2)��f(a)ͬ�ţ���˵����������[(a+b)/2,b]����a=(a+b)/2���ظ�ѭ����
���f((a+b)/2)��f(b)ͬ�ţ���˵����������[a,(a+b)/2]����b=(a+b)/2���ظ�ѭ����
����ĿҪ���д���򣬼������3�׶���ʽf(x)=a3*x^3 + a2*x^2 + a1*x + a0 �ڸ�������[a,b]�ڵĸ���

�����ʽ��
�����ڵ�1����˳���������ʽ��4��ϵ�� a3, a2, a1, a0, �ڵ�2����˳���������˵�a��b��
��Ŀ��֤����ʽ�ڸ��������ڴ���Ψһ������

�����ʽ��
��һ��������ö���ʽ�ڸ������ڵĸ�����ȷ��С�����2λ��

����������
3 -1 -3 1
-0.5 0.5
���������
0.33
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
double a0, a1, a2, a3;

double f(double x)
{
    return a3 * x * x * x + a2 * x * x + a1 * x + a0;
}

double fx(double a, double b)
{
    if (b - a < 0.000001) return (a + b) / 2;
    double fa = f(a);
    double fb = f(b);
    if (fa == 0) return a;
    if (fb == 0) return b;
    if (fa * fb < 0) {
        double fmid = f((a + b) / 2);
        if (fmid == 0) return (a + b) / 2;
        else if (fmid * fa > 0) {
            return fx((a + b) / 2, b);
        } else {
            return fx(a, (a + b) / 2);
        }
    } else {
        // ��������
    }
}

int main()
{
    int n, y, f;
    for (int n = 0; n < 100; n++) {
        printf("n=%d", n);
        int yes = 0;
        for (int y = 0; y < 100; y++) {
            for (int f = 0; f < 100; f++) {
                if (98 * f - 199 * y == n) {
                    printf("  %d.%02d\n", y, f);
                    yes = 1;
                }
            }
        }
        if (!yes) {
            printf("No\n");
        }
    }
    double a, b;
    scanf("%lf %lf %lf %lf\n", &a3, &a2, &a1, &a0);
    scanf("%lf %lf", &a, &b);
    double root = fx(a, b);
    printf("%.2lf", root);
}