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
static void display_solution(int* solu, int n, const statistics& stat, int wait_ms = dtl::WAIT_NO_WAIT)
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
