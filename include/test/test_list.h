#pragma once

#include "../util/util.h"
#include "../util/check.h"
#include "../util/op.h"
#include "../dtl/list.h"

namespace dtl
{
namespace test
{

//! 统一递增列表中的各元素
template <typename T>
void increase(List<T>& L)
{
	L.traverse(Increase<T>());
}

//! 统计向量、列表等具有traverse接口容器的特征（所有元素之和）
template <typename T>
void crc(List<T>& L)
{
	T crc = 0;
	L.traverse(CRC<T>(crc));
	printf("CRC=");
	print(crc);
	printf("\n");
}

//! 判断列表是否整体有序
template <typename T>
void checkOrder(List<T> & L) {
	int unsorted = 0; //逆序计数器
	L.traverse(CheckOrder<T>(unsorted, L.first()->data)); //进行遍历
	if (0 < unsorted)
		printf("Unsorted with %d adjacent disordered pair(s)\n", unsorted);
	else
		printf("Sorted\n");
	printf("DISORDERED = %d\n", L.disordered());
}

template <typename T>
static void PRINT(List<T>& L)
{
	print(L);
	crc(L);
	checkOrder(L);
}

//! 随机生成长度为n的列表（可能包含重复节点）
template <typename T>
void randomList(List<T>& list, int n) // 在[0, 2n)中选择n个偶数，随机插入列表
{
	auto p = (rand() % 2) ? list.insert_as_last(rand() % n * 2) : list.insert_as_first(rand() % n * 2);
	for (int i = 1; i < n; i++) {
		p = (rand() % 2) ? list.insert_before(p, rand() % n * 2) : list.insert_after(p, rand() % n * 2);
	}
}


template <typename T>
void testList(int testSize, int wait_ms = dtl::WAIT_NO_WAIT)
{
	int testID = 0;
	printf("\n  ==== Test %2d. Generate two lists each of size %d by random insertions\n", testID++, testSize);
	List<T> La; randomList(La, testSize); 
	PRINT(La);
	List<T> Lb; randomList(Lb, testSize); 
	PRINT(Lb);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Call list members by rank (with high complexity)\n", testID++);
	for (int i = 0; i < La.size(); i++) print(La[i]); 
	printf("\n");
	for (int i = 0; i < Lb.size(); i++) print(Lb[i]); 
	printf("\n");
	wait(wait_ms);

	printf("\n  ==== Test %2d. Concatenation\n", testID++); 
	PRINT(La); PRINT(Lb);
	while (0 < Lb.size()) La.insert_as_last(Lb.remove(Lb.first())); 
	PRINT(La); PRINT(Lb);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Increase\n", testID++);
	PRINT(La);
	increase(La);
	PRINT(La);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Lowpass (with high complexity) on\n", testID++); 
	PRINT(La);
	for (int i = La.size(); 0 < --i;) {
		La[i - 1] += La[i]; 
		La[i - 1] >>= 1;
	} 
	PRINT(La);
	wait(wait_ms);

	printf("\n  ==== Test %2d. reverse\n", testID++);
	La.reverse();
	PRINT(La);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Copy\n", testID++);
	PRINT(La);
	List<T> Ld(La);
	PRINT(Ld);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Trim by random deletions\n", testID++);
	PRINT(Ld);
	while (testSize / 4 < Ld.size()) {
		int N = rand() % Ld.size();
		printf("removing L[%d]=", N);
		auto p = Ld.first();
		while (0 < N--) p = p->succ;
		print(p->data);
		printf(" ...\n");
		Ld.remove(p);
		PRINT(Ld);
		wait(wait_ms);
	}
	wait(wait_ms);

	printf("\n  ==== Test %2d. Copy\n", testID++);
	PRINT(La);
	List<T> Le(La);
	PRINT(Le);
	wait(wait_ms);

	printf("\n  ==== Test %2d. FIND in\n", testID++);
	PRINT(Le);
	for (int i = 0; i <= testSize * 2; i++) { //逐一测试[0, 2n]中的所有可能
		auto p = Le.find((T)i);
		printf("Looking for ");
		print((T)i);
		printf(": ");
		if (p) { printf(" found with"); print(p->data); } else printf(" not found");
		printf("\n");
		wait(wait_ms);
	} //正确的结构应该是大致（n+1次）失败、（n次）成功相间
	wait(wait_ms);

	printf("\n  ==== Test %2d. Sort\n", testID++);
	PRINT(La);
	La.sort();
	PRINT(La);
	wait(wait_ms);

	printf("\n  ==== Test %2d. SEARCH in\n", testID++);
	PRINT(La);
	for (int i = 0; i <= testSize * 2; i++) { //逐一测试[0, 2n]中的所有可能
		auto p = La.search((T)i);
		printf("Looking for ");
		print((T)i);
		printf(": ");
		printf(" stopped at");
		print(p->data);
		if ((T)i == p->data) printf(" and found");
		printf("\n");
		wait(wait_ms);
	} //正确的结构应该是大致（n+1次）失败、（n次）成功相间
	wait(wait_ms);

	printf("\n  ==== Test %2d. Remove redundancy in\n", testID++);
	PRINT(La);
	printf("%d node(s) removed\n", La.uniquify());
	PRINT(La);
	La.reverse();
	PRINT(La);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Remove redundancy in\n", testID++);
	PRINT(Le);
	printf("%d node(s) removed\n", Le.deduplicate());
	PRINT(Le);
	wait(wait_ms);

	printf("\n  ==== Test %2d. Sort\n", testID++);
	PRINT(Le);
	Le.sort();
	PRINT(Le);
	wait(wait_ms);

#if ENABLE_INITIALIZER_LIST
	printf("\n==== Test %2d. Construct from initializer_list\n", testID++);
	List<T> li = { 0,1,2,3,4,5 };
	PRINT(li);
	wait(wait_ms);
#endif
}

}
}
