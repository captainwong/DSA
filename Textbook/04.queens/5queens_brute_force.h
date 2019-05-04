#pragma once
#include "../../include/util/util.h"

//! ͳ��
struct statistics
{
	//! ��ѡ������
	int candidate = 0;
	//! ��ͻ������
	int check = 0;
	//! �����������
	int solution = 0;
};

//! �ж��Ƿ�����ڵ�ǰ�еĵ�k�з�����һ���ʺ�
static bool collide(int* solu, int k, statistics& stat)
{
	stat.check++;
	for (int i = 0; i < k; i++) {
		if ((solu[k] == solu[i]) || // ͬ��
			(solu[k] - solu[i] == k - i) || // �Խ���
			(solu[k] - solu[i] == i - k)) // ���Խ���
			return true;
	}
	return false;
}

//! ���n*n�Ŀ��в���
static void display_solution(int* solu, int n, const statistics& stat, int wait_ms = 0)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf((j == solu[i]) ? "��" : "[]");
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

//! 5�ʺ������㷨
static void place_5_queens_brute_force(statistics& stat, int wait_ms = 0)
{
	// �±�Ϊ�У�ֵΪ��
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