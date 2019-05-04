#pragma once
#include "../../include/util/util.h"

//! 统计
struct statistics
{
	//! 候选解数量
	int candidate = 0;
	//! 冲突检测次数
	int check = 0;
	//! 解决方案数量
	int solution = 0;
};

//! 判断是否可以在当前行的第k列放置下一个皇后
static bool collide(int* solu, int k, statistics& stat)
{
	stat.check++;
	for (int i = 0; i < k; i++) {
		if ((solu[k] == solu[i]) || // 同列
			(solu[k] - solu[i] == k - i) || // 对角线
			(solu[k] - solu[i] == i - k)) // 反对角线
			return true;
	}
	return false;
}

//! 输出n*n的可行布局
static void display_solution(int* solu, int n, const statistics& stat, int wait_ms = 0)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf((j == solu[i]) ? "█" : "[]");
		}
		printf("\n");
	}

	if (wait_ms < 0) {
		printf("%d solution(s) found after %d check(s)\n", stat.solution, stat.check);
		dtl::wait(wait_ms);
	} else {
		printf("\n");
	}
}

//! 5皇后蛮力算法
static void place_5_queens_brute_force(statistics& stat, int wait_ms = 0)
{
	// 下标为行，值为列
	int solu[5] = { 0 };
	for (solu[0] = 0; solu[0] < 5; solu[0]++) {
		for (solu[1] = 0; solu[1] < 5; solu[1]++) {
			for (solu[2] = 0; solu[2] < 5; solu[2]++) {
				for (solu[3] = 0; solu[3] < 5; solu[3]++) {
					for (solu[4] = 0; solu[4] < 5; solu[4]++) {
						stat.candidate++;
						if (collide(solu, 0, stat) ||
							collide(solu, 1, stat) ||
							collide(solu, 2, stat) ||
							collide(solu, 3, stat) ||
							collide(solu, 4, stat))
							continue;

						stat.solution++;
						display_solution(solu, 5, stat, wait_ms);

					}
				}
			}
		}
	}

	printf("%d Queens, %d Solution(s), %d Candidate(s), %d Check(s)\n", 5, stat.solution, stat.candidate, stat.check);
}