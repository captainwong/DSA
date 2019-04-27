#pragma once

#include "../dtl/priority_queue.h"
#include "../util/util.h"
#include <thread>
#include <chrono>

namespace dtl
{
namespace test
{

template <typename PQType, typename T>
static void priority_queue_test(int n, size_t gap_ms = 1000)
{
	auto A = new T[2 * n / 3];
	for (int i = 0; i < 2 * n / 3; i++) {
		A[i] = dice(static_cast<T>(n) * 3);
	}
	printf("%d random keys created:\n", 2 * n / 3);
	for (int i = 0; i < 2 * n / 3; i++) {
		print(A[i]);
	}printf("\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(gap_ms));
	PQType heap(A + n / 6, n / 3); delete[] A;
	system("cls"); print(heap); std::this_thread::sleep_for(std::chrono::milliseconds(gap_ms));
	while (heap.size() < n) {
		if (dice(100) < 70) {
			T e = dice(static_cast<T>(n) * 3);
			printf("Inserting");
			print(e);
			printf(" ...\n");
			heap.insert(e);
			printf("Insertion done\n");
		} else {
			if (!heap.empty()) {
				printf("Deleting max ...\n");
				auto e = heap.delMax();
				printf("Deletion done with");
				print(e);
				printf("\n");
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(gap_ms));
		system("cls");
		print(heap);
		std::this_thread::sleep_for(std::chrono::milliseconds(gap_ms));
	}

	while (!heap.empty()) {
		auto e = heap.delMax();
		printf("Deletion done with");
		print(e);
		printf("\n"); 
		std::this_thread::sleep_for(std::chrono::milliseconds(gap_ms));
		system("cls");
		print(heap);
		std::this_thread::sleep_for(std::chrono::milliseconds(gap_ms));
	}
}

}
}
