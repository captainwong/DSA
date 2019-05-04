#pragma once

#include "queen.h"

// ºÙ÷¶∞Ê

//! 2ª ∫ÛºÙ÷¶∞Ê
static void place_2_queens_pruning(statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
{
	printf("place_2_queens_pruning\n");
	int solu[2] = { 0 };
	for (solu[0] = 0; solu[0] < 2; solu[0]++) {
		// if (!collide(solu, 0, stat)) // “˛∫¨ºÙ÷¶£¨µ´ÕÍ»´√ª±ÿ“™
		for (solu[1] = 0; solu[1] < 2; solu[1]++) {
			if (!collide(solu, 1, stat)) { // ºÙ÷¶
				stat.solution++;
				display_solution(solu, 2, stat, wait_ms);
			}
		}
	}
	printf("%d Queens, %d Solution(s), %d Check(s)\n\n", 2, stat.solution, stat.check);
}

//! 3ª ∫ÛºÙ÷¶∞Ê
static void place_3_queens_pruning(statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
{
	printf("place_3_queens_pruning\n");
	int solu[3] = { 0 };
	for (solu[0] = 0; solu[0] < 3; solu[0]++) {
		// if (!collide(solu, 0, stat)) // “˛∫¨ºÙ÷¶£¨µ´ÕÍ»´√ª±ÿ“™
		for (solu[1] = 0; solu[1] < 3; solu[1]++) {
			if (!collide(solu, 1, stat)) { // ºÙ÷¶
				for (solu[2] = 0; solu[2] < 3; solu[2]++) {
					if (!collide(solu, 2, stat)) { // ºÙ÷¶
						stat.solution++;
						display_solution(solu, 3, stat, wait_ms);
					}
				}				
			}
		}
	}
	printf("%d Queens, %d Solution(s), %d Check(s)\n\n", 3, stat.solution, stat.check);
}

//! 4ª ∫ÛºÙ÷¶∞Ê
static void place_4_queens_pruning(statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
{
	printf("place_4_queens_pruning\n");
	int solu[4] = { 0 };
	for (solu[0] = 0; solu[0] < 4; solu[0]++) {
		// if (!collide(solu, 0, stat)) // “˛∫¨ºÙ÷¶£¨µ´ÕÍ»´√ª±ÿ“™
		for (solu[1] = 0; solu[1] < 4; solu[1]++) {
			if (!collide(solu, 1, stat)) { // ºÙ÷¶
				for (solu[2] = 0; solu[2] < 4; solu[2]++) {
					if (!collide(solu, 2, stat)) { // ºÙ÷¶
						for (solu[3] = 0; solu[3] < 4; solu[3]++) {
							if (!collide(solu, 3, stat)) { // ºÙ÷¶
								stat.solution++;
								display_solution(solu, 4, stat, wait_ms);
							}
						}
					}
				}
			}
		}
	}
	printf("%d Queens, %d Solution(s), %d Check(s)\n\n", 4, stat.solution, stat.check);
}

//! 5ª ∫ÛºÙ÷¶∞Ê
static void place_5_queens_pruning(statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
{
	printf("place_5_queens_pruning\n");
	int solu[5] = { 0 };
	for (solu[0] = 0; solu[0] < 5; solu[0]++) {
		// if (!collide(solu, 0, stat)) // “˛∫¨ºÙ÷¶£¨µ´ÕÍ»´√ª±ÿ“™
		for (solu[1] = 0; solu[1] < 5; solu[1]++) {
			if (!collide(solu, 1, stat)) { // ºÙ÷¶
				for (solu[2] = 0; solu[2] < 5; solu[2]++) {
					if (!collide(solu, 2, stat)) { // ºÙ÷¶
						for (solu[3] = 0; solu[3] < 5; solu[3]++) {
							if (!collide(solu, 3, stat)) { // ºÙ÷¶
								for (solu[4] = 0; solu[4] < 5; solu[4]++) {
									if (!collide(solu, 4, stat)) { // ºÙ÷¶
										stat.solution++;
										display_solution(solu, 5, stat, wait_ms);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("%d Queens, %d Solution(s), %d Check(s)\n\n", 5, stat.solution, stat.check);
}


static void place_n_queens_prunning_impl(int* solu, int i, int n, statistics& stat, int wait_ms)
{
	for (solu[i] = 0; solu[i] < n; solu[i]++) {
		if (!collide(solu, i, stat)) {
			if (i + 1 == n) {
				stat.solution++;
				display_solution(solu, n, stat, wait_ms);
			} else {
				place_n_queens_prunning_impl(solu, i + 1, n, stat, wait_ms);
			}
		}
	}
};

static void place_n_queens_prunning(int n, statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
{
	auto solu = new int[n];
	place_n_queens_prunning_impl(solu, 0, n, stat, wait_ms);
	delete[] solu;
	printf("%d Queens, %d Solution(s), %d Check(s)\n\n", n, stat.solution, stat.check);
}