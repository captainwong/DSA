#pragma once

#include "priority_queue.h"
#include "bintree.h"
#include "comparator.h"
#include "swap.h"

namespace dtl
{

//! 左式堆
template <typename T>
class LeftHeap : public PriorityQueue<T>, public BinTree<T>
{
public:
	typedef BinNode<T> Node;
	typedef Node* NodePtr;
	typedef BinTree<T> BinTreeType;

	LeftHeap() {}

	LeftHeap(T* E, int n) {
		for (int i = 0; i < n; i++) {
			insert(E[i]);
		}
	}

	void insert(T const& e) {
		auto v = new Node(e);
		BinTreeType::root_ = merge(BinTreeType::root_, v);
		BinTreeType::size_++;
	}

	T getMax() {
		return BinTreeType::root_->data_;
	}

	T delMax() {
		auto l = BinTreeType::root_->lChild_;
		auto r = BinTreeType::root_->rChild_;
		auto e = BinTreeType::root_->data_;
		delete BinTreeType::root_;
		BinTreeType::size_--;
		BinTreeType::root_ = merge(l, r);
		if (BinTreeType::root_) { BinTreeType::root_->parent_ = nullptr; }
		return e;
	}

protected:
	static NodePtr merge(NodePtr a, NodePtr b) {
		if (!a) { return b; }
		if (!b) { return a; }
		if (lt(a->data_, b->data_)) { swap(a, b); }
		a->rChild_ = merge(a->rChild_, b);
		a->rChild_->parent_ = a;
		if (!a->lChild_ || a->lChild_->height_ < a->rChild_->height_) {
			swap(a->lChild_, a->rChild_);
		}
		a->height_ = a->rChild_ ? a->rChild_->height_ + 1 : 1;
		return a;
	}
};

}
