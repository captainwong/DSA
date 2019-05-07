#pragma once

#include "../util/util.h"
#include "../util/check.h"
#include "../util/op.h"
#include "../dtl/stack.h"

namespace dtl
{
namespace test
{

template <typename T>
void testStack(int n, int wait_ms = WAIT_NO_WAIT)
{
	int testID = 0;
	Stack<T> S;
	srand_time();

	printf("\n ==== Test %d. Growing stack\n", testID++);
	while (S.size() < n) {
		T e = rand() % (2 * n);
		if (S.empty() || (30 < (rand() % 100))) { // 70%概率入栈
			printf("pushing "); print(e); printf(" ...\n");
			S.push(e);
		} else { // 30%概率出栈
			printf("poping "); print(S.pop()); printf(" ...\n");
		}
		print(S);
	}

	printf("\n ==== Test %d. Shrinking stack\n", testID++);
	while (!S.empty()) {
		T e = dice((T)2 * n);
		if (70 < dice(100)) { // 30%概率入栈
			printf("pushing "); print(e); printf(" ...\n");
			S.push(e);
		} else { // 70%概率出栈
			printf("poping with ... "); print(S.pop()); printf("\n");
		}
		print(S);
	}
}

}
}
