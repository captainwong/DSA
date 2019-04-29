#pragma once

namespace dtl 
{

//! 秩
typedef int Rank;

//! 链表节点
template <typename T>
struct ListNode
{
	typedef ListNode<T> Node;
	typedef Node* Ptr;

	//! 数据
	T data;
	//! 前驱
	Ptr pred;
	//! 后继
	Ptr succ;

	ListNode() : data(), pred(nullptr), succ(nullptr) {}

	ListNode(T e, Ptr p = nullptr, Ptr s = nullptr)
		: data(e), pred(p), succ(s)
	{}

	Ptr insert_as_pred(T const& e) {
		auto node = new Node(e, pred, this);
		if (pred) {
			pred->succ = node;
		}
		pred = node;
		return node;
	}

	Ptr insert_as_succ(T const& e) {
		auto node = new Node(e, this, succ);
		if (succ) {
			succ->pred = node;
		}
		succ = node;
		return node;
	}
};

}
