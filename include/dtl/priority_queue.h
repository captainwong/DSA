#pragma once

#include "comparator.h"
#include "swap.h"
#include "vector.h"

namespace dtl
{

//! 优先级队列接口定义
template <typename T>
struct PriorityQueue
{
	//! 按照比较器确定的优先级次序插入词条
	virtual void insert(T const&) = 0;
	//! 获取优先级最高的词条
	virtual T getMax() = 0;
	//! 删除优先级最高的词条
	virtual T delMax() = 0;
};


//! 基于向量，以完全二叉堆形式实现的优先级队列
template <typename T>
class CompleteHeap : public PriorityQueue<T>, public Vector<T>
{
public:
	typedef PriorityQueue<T> PQType;
	typedef Vector<T> VectorType;

	CompleteHeap() {}
	
	CompleteHeap(T* A, Rank lo, Rank hi) {
		VectorType::copy_from(A, lo, hi);
		heapify(hi - lo);
	}

	CompleteHeap(T* A, Rank n) {
		VectorType::copy_from(A, 0, n);
		heapify(n);
	}

	void insert(T const& e) {
		VectorType::insert(e);
		percolateUp(VectorType::size_ - 1);
	}

	T getMax() {
		return VectorType::elem_[0];
	}

	T delMax() {
		auto maxElem = VectorType::elem_[0];
		VectorType::elem_[0] = VectorType::remove(VectorType::size_ - 1);
		percolateDown(VectorType::size_, 0);
		return maxElem;
	}

	/*****************helpers*******************/
	
	inline bool inHeap(Rank i) const { return -1 < i && i < VectorType::size_; }
	inline bool hasParent(Rank i) const { return 0 < i; }
	inline Rank parent(Rank i) const { return (i - 1) >> 1; }
	inline Rank lChild(Rank i) const { return 1 + (i << 1); }
	inline Rank rChild(Rank i) const { return (1 + i) << 1; }
	inline bool hasLChild(Rank i) const { return inHeap(lChild(i)); }
	inline bool hasRChild(Rank i) const { return inHeap(rChild(i)); }
	inline Rank bigger(Rank i, Rank j) const { return lt(VectorType::elem_[i], VectorType::elem_[j]) ? j : i; }
	inline Rank properParent(Rank i) const {
		return hasRChild(i) ? bigger(bigger(i, lChild(i)), rChild(i)) : (hasLChild(i) ? bigger(i, lChild(i)) : i);
	}
	inline Rank lastInternal(Rank n) const { return parent(n - 1); }

protected:
	//! 下滤
	Rank percolateDown(Rank n, Rank i) {
		Rank j;
		while (i != (j = properParent(i))) {
			swap(VectorType::elem_[i], VectorType::elem_[j]);
			i = j;
		}
		return i;
	}

	//! 上滤
	Rank percolateUp(Rank i) {
		while (hasParent(i)) {
			auto j = parent(i);
			if (lt(VectorType::elem_[i], VectorType::elem_[j])) {
				break;
			}
			swap(VectorType::elem_[i], VectorType::elem_[j]);
			i = j;
		}
		return i;
	}

	//! Floyd建堆算法 O(n)
	void heapify(Rank n) {
		for (int i = lastInternal(n); inHeap(i); i--) {
			percolateDown(n, i);
		}
	}
};

}
