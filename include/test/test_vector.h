#pragma once

#include "../util/util.h"
#include "../util/check.h"
#include "../util/op.h"
#include "../dtl/vector.h"
#include <limits.h> // INT_MAX

namespace dtl
{
namespace test
{

//! 统一递增向量中的各元素
template <typename T>
void increase(Vector<T>& v)
{
	v.traverse(Increase<T>());
}

//! 统计向量、列表等具有traverse接口容器的特征（所有元素之和）
template <typename T>
void crc(Vector<T>& v)
{
	T crc = 0;
	v.traverse(CRC<T>(crc));
	printf("CRC=");
	print(crc);
	printf("\n");
}

//! 判断向量是否整体有序
template <typename T> 
void checkOrder(Vector<T> & V) { 
	int unsorted = 0; //逆序计数器
	V.traverse(CheckOrder<T>(unsorted, V[0])); //进行遍历
	if (0 < unsorted)
		printf("Unsorted with %d adjacent disordered pair(s)\n", unsorted);
	else
		printf("Sorted\n");
}

//! 随机置乱
template <typename T>
void permute(Vector<T>& v)
{
	for (int i = v.size(); i > 0; i--) { // 自后向前
		swap(v[i - 1], v[rand() % i]); // V[i - 1]与v[0, i)中某一随机元素交换
	}
}

template <typename T>
static void printV(Vector<T>& v)
{
	print(v);
	crc(v);
	checkOrder(v);
}

//! 测试：无序向量的（顺序）查找
template <typename T>
void testFind(Vector<T>& v, int n)
{
	for (int i = 0; i < v.size(); i++) { //依次查找向量中元素，当然成功
		T e = v[i]; print(e);
		Rank r = v.find(e);
		if (r < 0) printf(" : not found until rank v[%d] <> %d", r, e);
		else printf(" : found at rank v[%d] = %d", r, v[r]);
		printf("\n");
	}

	for (int i = 0; i <= v.size(); i++) { //依次查找每对相邻元素的均值，可能成功
		T a = (0 < i) ? v[i - 1] : -INT_MAX / 2;
		T b = (i < v.size()) ? v[i] : INT_MAX / 2;
		T e = (a + b) / 2; print(e);
		Rank r = v.find(e);
		if (r < 0) printf(" : not found until rank v[%d] <> %d", r, e);
		else printf(" : found at rank v[%d] = %d", r, v[r]);
		printf("\n");
	}
}

//! 测试：有序向量的查找（binSearch或fibSearch）
template <typename T> //元素类型
void testSearch(Vector<T> & V) {
	for (int i = 0; i < V.size(); i++) { //依次查找向量中元素，当然成功
		T e = V[i]; printf("Looking for"); print(e); printf(" in ...\n"); print(V);
		Rank r = V.search(e);
		if (V[r] == e) printf("found at rank V[%d] = %d", r, V[r]);
		else printf("found at rank V[%d] = %d <> %d\a\a", r, V[r], e);
		printf("\n\n");
	}
	for (int i = 0; i <= V.size(); i++) { //依次相邻元素的均值，可能成功
		T a = (0 < i) ? V[i - 1] : -INT_MAX / 2;
		T b = (i < V.size()) ? V[i] : INT_MAX / 2;
		T e = (a + b) / 2; printf("Looking for"); print(e); printf(" in ...\n"); print(V);
		Rank r = V.search(e);
		printf("V[%-3d] =", r); (r < 0) ? print("-INF") : print(V[r]); printf("  ~  ");
		printf("V[%-3d] =", r + 1); (r + 1 < V.size()) ? print(V[r + 1]) : print("+INF");
		bool ordered = true;
		if ((r >= 0) && (V[r] > e)) ordered = false;
		if ((r + 1 < V.size()) && (V[r + 1] <= e)) ordered = false;
		if (!ordered) printf("\tincorrect search\a\a");
		printf("\n\n");
	}
}

//! 测试：有序向量的插入
template <typename T> //元素类型
void testOrderedInsertion(Vector<T> & V, int n) 
{
	while (n * 2 > V.size()) {
		T e = dice((T)n * 2);
		printf("Inserting "); print(e); printf(" ...\n");
		V.insert(V.search(e) + 1, e);
		print(V);
	}
}

template <typename T>
static void testVector(int testSize, int wait_ms = dtl::WAIT_NO_WAIT)
{
	srand_time();
	int testId = 0;

	printf("\n==== Test %2d. Generate a random vector\n", testId++);
	Vector<T> v;
	// 在[0, 3n)中选择n个数，随机插入向量
	for (int i = 0; i < testSize; i++) {
		v.insert(dice(i + 1), dice(static_cast<T>(testSize) * 3));
	}
	printV(v);
	permute(v);
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. Lowpass on\n", testId++);
	printV(v);
	for (int i = v.size(); --i;) {
		v[i - 1] += v[i];
		v[i - 1] >>= 1;
	}
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. Increase\n", testId++);
	printV(v);
	increase(v);
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. FIND in\n", testId++);
	printV(v);
	testFind(v, testSize);
	wait(wait_ms);

	printf("\n==== Test %2d. Sort degenerate intervals each of size 1 in\n", testId++);
	printV(v);
	for (int i = 0; i < v.size(); i += v.size() / 5) {
		v.sort(i, i);
		printV(v);
	}
	wait(wait_ms);

	printf("\n==== Test %2d. Sort 5 intervals each of size %d in\n", testId++, v.size());
	printV(v);
	for (int i = 0; i < v.size(); i += v.size() / 5) {
		v.sort(i, __min(v.size(), i + v.size() / 5));
		printV(v);
		wait(wait_ms);
	}

	printf("\n==== Test %2d. Sort the entire vector of\n", testId++);
	printV(v);
	v.sort();
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. FIND in\n", testId++);
	printV(v);
	testFind(v, testSize);
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. SEARCH in\n", testId++);
	printV(v);
	testSearch(v);
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. Unsort [%d, %d) in\n", testId++, v.size() / 4, 3 * v.size() / 4);
	printV(v);
	v.unsort(v.size() / 4, 3 * v.size() / 4);
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. Unsort [%d, %d) in\n", testId++, 0, v.size());
	printV(v);
	v.unsort();
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. Copy [%d, %d) from\n", testId++, v.size() / 4, 3 * v.size() / 4);
	printV(v);
	Vector<T> U(v, v.size() / 4, 3 * v.size() / 4);
	printV(U);
	wait(wait_ms);

	printf("\n==== Test %2d. Copy from\n", testId++);
	printV(v);
	Vector<T> W(v);
	printV(W);
	wait(wait_ms);

	printf("\n==== Test %2d. Clone from\n", testId++);
	printV(U);
	W = U;
	printV(W);
	wait(wait_ms);

	printf("\n==== Test %2d. Remove redundancy in unsorted\n", testId++);
	printV(v);
	printf("%d node(s) removed\n", v.deduplicate());
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. Sort [%d, %d) in\n", testId++, 0, v.size());
	printV(v);
	v.sort();
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. FIND in\n", testId++);
	printV(v);
	testOrderedInsertion(v, testSize);
	printV(v);
	wait(wait_ms);

	printf("\n==== Test %2d. Remove redundancy in sorted\n", testId++);
	printV(v);
	printf("%d node(s) removed\n", v.uniquify());
	printV(v);
	wait(wait_ms);
}

}
}
