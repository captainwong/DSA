

/*
// https://pintia.cn/problem-sets/14/problems/795
���������Ŀ�� 7-15 ����Բ����

���������ϵʽ����Բ���ʵ�ֵ��ֱ�����һ���ֵС�ڸ�����ֵ��
pi/2 = 1 + 1/3 + 2!/(3x5) + 3!/(3x5x7) + ... + n!/(3x5x7x...x(2n+1)) + ...

�����ʽ��
������һ���и���С��1����ֵ��

�����ʽ��
��һ�������������ֵ�����Ľ���Բ���ʣ������С�����6λ��

����������
0.01
���������
3.132157


��ʾ��ֱ�Ӽ���׳˻ᳬ������
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