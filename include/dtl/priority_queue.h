#pragma once

#include "comparator.h"
#include "swap.h"
#include "vector.h"

namespace dtl
{

//! ���ȼ����нӿڶ���
template <typename T>
struct PriorityQueue
{
	//! ���ձȽ���ȷ�������ȼ�����������
	virtual void insert(T const&) = 0;
	//! ��ȡ���ȼ���ߵĴ���
	virtual T getMax() = 0;
	//! ɾ�����ȼ���ߵĴ���
	virtual T delMax() = 0;
};


//! ��������������ȫ�������ʽʵ�ֵ����ȼ�����
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
	//! ����
	Rank percolateDown(Rank n, Rank i) {
		Rank j;
		while (i != (j = properParent(i))) {
			swap(VectorType::elem_[i], VectorType::elem_[j]);
			i = j;
		}
		return i;
	}

	//! ����
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

	//! Floyd�����㷨 O(n)
	void heapify(Rank n) {
		for (int i = lastInternal(n); inHeap(i); i--) {
			percolateDown(n, i);
		}
	}
};

}
