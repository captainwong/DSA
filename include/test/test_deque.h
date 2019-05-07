#pragma once

#include "../util/util.h"
#include "../dtl/deque.h"

namespace dtl
{
namespace test
{

template <typename T>
void testDeque(int n, int wait_ms = WAIT_NO_WAIT)
{
	int testID = 0;
	Deque<T> Q;

	printf("\n  ==== Test %2d. Growing deque\n", testID++);
	while (Q.size() < n) {
		if (Q.empty() || (30 < dice(100))) { // 70%入队
			T e = dice((T)2 * n);
			if (rand() % 2) { // 50%插入队首
				printf("push_front "); print(e); printf(" ...\n");
				Q.push_front(e);
			} else { // 50%插入队尾
				printf("push_back "); print(e); printf(" ...\n");
				Q.push_back(e);
			}
		} else { // 30%出队
			if (rand() % 2) {
				printf("pop_front "); print(Q.pop_front()); printf(" ...\n");
			} else {
				printf("pop_back "); print(Q.pop_back()); printf(" ...\n");
			}
			
		}

		print(Q);
	}

	printf("\n  ==== Test %2d. Shrinking deque\n", testID++);
	while (!Q.empty()) {
		if (Q.empty() || (70 < dice(100))) { // 70%入队
			T e = dice((T)2 * n);
			if (rand() % 2) { // 50%插入队首
				printf("push_front "); print(e); printf(" ...\n");
				Q.push_front(e);
			} else { // 50%插入队尾
				printf("push_back "); print(e); printf(" ...\n");
				Q.push_back(e);
			}
		} else { // 30%出队
			if (rand() % 2) {
				printf("pop_front "); print(Q.pop_front()); printf(" ...\n");
			} else {
				printf("pop_back "); print(Q.pop_back()); printf(" ...\n");
			}

		}
		print(Q);
	}
}

}
}
