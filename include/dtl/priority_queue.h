#pragma once

#include "vector.h"
#include "swap.h"

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
	//! ����
	Rank percolateDown(Rank n, Rank i);
	//! ����
	Rank percolateUp(Rank i);
	//! Floyd�����㷨
	void heapify(Rank n);
};

}
