#pragma once

#include "queen.h"

// 蛮力版

//! 5皇后蛮力算法
static void place_5_queens_brute_force(statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
{
	printf("place_5_queens_brute_force\n");
	// 下标为行，值为列
	int solu[5] = { 0 };
	for (solu[0] = 0; solu[0] < 5; solu[0]++) {
		for (solu[1] = 0; solu[1] < 5; solu[1]++) {
			for (solu[2] = 0; solu[2] < 5; solu[2]++) {
				for (solu[3] = 0; solu[3] < 5; solu[3]++) {
					for (solu[4] = 0; solu[4] < 5; solu[4]++) {
						stat.candidate++;
						if (/*collide(solu, 0, stat) ||*/ // 完全可以省略
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
	printf("%d Queens, %d Solution(s), %d Candidate(s), %d Check(s)\n\n", 5, stat.solution, stat.candidate, stat.check);
}
