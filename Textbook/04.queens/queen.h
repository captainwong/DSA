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
static void display_solution(int* solu, int n, const statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
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
