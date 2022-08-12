

/*
// https://pintia.cn/problem-sets/14/problems/795
基础编程题目集 7-15 计算圆周率

根据下面关系式，求圆周率的值，直到最后一项的值小于给定阈值。
pi/2 = 1 + 1/3 + 2!/(3x5) + 3!/(3x5x7) + ... + n!/(3x5x7x...x(2n+1)) + ...

输入格式：
输入在一行中给出小于1的阈值。

输出格式：
在一行中输出满足阈值条件的近似圆周率，输出到小数点后6位。

输入样例：
0.01
输出样例：
3.132157


提示：直接计算阶乘会超长整型
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

double nth_element(int N)
{
	if (N == 1)return 1.0 / 3;
	if (N == 2)return 2.0 / 15;
	long n = 2, d = 1;
	if (N % 2 == 1) {
		for (int i = 4; i <= N - 1; i += 2) {
			n *= i;
		}
		for (int i = N + 2; i <= 2 * N + 1; i += 2) {
			d *= i;
		}
	} else {
		for (int i = 4; i <= N; i += 2) {
			n *= i;
		}
		for (int i = N + 1; i <= N * 2 + 1; i += 2) {
			d *= i;
		}
	}
	return n * 1.0l / d;
}

int main()
{
	double threshold;
	scanf("%lf", &threshold);
	double half_pi = 1;
	int n = 1;
	double nth;
	do {
		nth = nth_element(n++);
		half_pi += nth;
	} while (nth >= threshold);
	printf("%.6lf", half_pi * 2);
}