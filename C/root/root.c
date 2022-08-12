/*
https://pintia.cn/problem-sets/14/problems/798
基础编程题目集 7-18 二分法求多项式单根
分数 20
作者 杨起帆
单位 浙大城市学院
二分法求函数根的原理为：如果连续函数f(x)在区间[a,b]的两个端点取值异号，即f(a)f(b)<0，
则它在这个区间内至少存在1个根r，即f(r)=0。

二分法的步骤为：

检查区间长度，如果小于给定阈值，则停止，输出区间中点(a+b)/2；否则
如果f(a)f(b)<0，则计算中点的值f((a+b)/2)；
如果f((a+b)/2)正好为0，则(a+b)/2就是要求的根；否则
如果f((a+b)/2)与f(a)同号，则说明根在区间[(a+b)/2,b]，令a=(a+b)/2，重复循环；
如果f((a+b)/2)与f(b)同号，则说明根在区间[a,(a+b)/2]，令b=(a+b)/2，重复循环。
本题目要求编写程序，计算给定3阶多项式f(x)=a3*x^3 + a2*x^2 + a1*x + a0 在给定区间[a,b]内的根。

输入格式：
输入在第1行中顺序给出多项式的4个系数 a3, a2, a1, a0, 在第2行中顺序给出区间端点a和b。
题目保证多项式在给定区间内存在唯一单根。

输出格式：
在一行中输出该多项式在该区间内的根，精确到小数点后2位。

输入样例：
3 -1 -3 1
-0.5 0.5
输出样例：
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
        // 根不存在
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