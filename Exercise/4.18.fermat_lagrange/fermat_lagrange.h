#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <math.h>
#include <stdio.h>
#include "../../include/dtl/vector.h"

struct FermatLagrange
{
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	void print() const {
		printf("[%d,%d,%d,%d]", a, b, c, d);
	}
};

struct Statistics
{
	int candidate = 0;
	int check = 0;
	int solution = 0;
};

// a) 暴力解（终点计算到sqrt(n)+1，是不是剪枝？）
static void fermatLagrange_a_brute_force(int n)
{
	FermatLagrange fermat;
	Statistics stat;
	int sq = static_cast<int>(sqrt(n)) + 1;
	for (int a = 0; a < sq; a++) {
		for (int b = 0; b < sq; b++) {
			for (int c = 0; c < sq; c++) {
				for (int d = 0; d < sq; d++) {
					stat.candidate++;
					if (a * a + b * b + c * c + d * d == n) {						
						fermat.a = a;
						fermat.b = b;
						fermat.c = c;
						fermat.d = d;
						printf("Found Fermat-Lagrange for %d with %d candidate(s): ", n, stat.candidate);
						fermat.print();
						return;
					}
				}
			}
		}
	}

}

// b) 暴力解（排除同一组数的不同排列，是不是剪枝？还有没有其他剪枝方法？）
static void fermatLagrange_b_brute_force(int n)
{
	Statistics stat;
	dtl::Vector<FermatLagrange> fermats;
	int sq = static_cast<int>(sqrt(n)) + 1;
	for (int a = 0; a < sq; a++) {
		for (int b = a; b < sq; b++) {
			for (int c = b; c < sq; c++) {
				for (int d = c; d < sq; d++) {
					stat.candidate++;
					if (a * a + b * b + c * c + d * d == n) {
						FermatLagrange fermat;
						fermat.a = a;
						fermat.b = b;
						fermat.c = c;
						fermat.d = d;
						fermats.insert(fermat);
						stat.solution++;
					}
				}
			}
		}
	}
	printf("Fermat-Lagrange for %d, %d solution(s) %d candidate(s):\n", n, stat.solution, stat.candidate);
	int i = 0;
	auto trav = [&i](FermatLagrange& f) {
		printf("#%d ", i++);  f.print(); printf("\n");
	};
	fermats.traverse(trav); printf("\n");
}

// c) 暴力解
static int countFermatLangrange(int n)
{
	static auto impl = [](int n, Statistics& stat) {
		int sq = static_cast<int>(sqrt(n)) + 1;
		for (int a = 0; a < sq; a++) {
			for (int b = a; b < sq; b++) {
				for (int c = b; c < sq; c++) {
					for (int d = c; d < sq; d++) {
						stat.candidate++;
						if (a * a + b * b + c * c + d * d == n) {
							stat.solution++;
						}
					}
				}
			}
		}
	};

	Statistics stat = {};
	for (int i = 0; i < n; i++) {
		impl(i, stat);
	}
	printf("%d Fermat-Langranges for number in [0,%d), %d candidate(s) checked", stat.solution, n, stat.candidate);
	return stat.solution;
}
