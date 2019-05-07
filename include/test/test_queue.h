#pragma once

#include "../util/util.h"
#include "../dtl/queue.h"

namespace dtl
{
namespace test
{

template <typename T>
void testQueue(int n, int wait_ms = WAIT_NO_WAIT)
{
	int testID = 0;
	Queue<T> Q;

	printf("\n  ==== Test %2d. Growing queue\n", testID++);
	while (Q.size() < n) {
		if (Q.empty() || (30 < dice(100))) { // 70%入队
			T e = dice((T)2 * n);
			printf("enqueue "); print(e); printf(" ...\n");
			Q.enqueue(e);
		} else { // 30%出队
			printf("dequeue "); print(Q.dequeue()); printf(" ...\n");
		}
			
		print(Q);
	}

	printf("\n  ==== Test %2d. Shrinking queue\n", testID++);
	while (!Q.empty()) {
		if (Q.empty() || (70 < dice(100))) { // 30%入队
			T e = dice((T)2 * n);
			printf("enqueue "); print(e); printf(" ...\n");
			Q.enqueue(e);
		} else { // 70%出队
			printf("dequeue "); print(Q.dequeue()); printf(" ...\n");
		}
		print(Q);
	}
}

}
}
