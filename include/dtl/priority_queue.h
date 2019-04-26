#pragma once

#include "vector.h"
#include "swap.h"

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
class ComplateHeap : public PriorityQueue<T>, public Vector<T>
{
public:
	typedef PriorityQueue<T> PQType;
	typedef Vector<T> VectorType;

	ComplateHeap() {}
	
	ComplateHeap(T* A, Rank lo, Rank hi) {
		VectorType::copy_from(A, lo, hi);
		heapify(hi - lo);
	}

	ComplateHeap(T* A, Rank n) {
		VectorType::copy_from(A, 0, n);
		heapify(n);
	}

	void insert(T const& e) {
		VectorType::::insert(e);
		percolateUp(VectorType::_size - 1);
	}

	T getMax() {
		return VectorType::_elem[0];
	}

	T delMax();

protected:
	//! 下滤
	Rank percolateDown(Rank n, Rank i);
	//! 上滤
	Rank percolateUp(Rank i);
	//! Floyd建堆算法
	void heapify(Rank n);
};

}
