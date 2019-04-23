#pragma once

typedef int Rank;

template <typename T>
struct ListNode
{
	T data;

	typedef ListNode<T>* Ptr;

	Ptr pred;
	Ptr succ;

	ListNode() : data(0), pred(nullptr), succ(nullptr) {}

	ListNode(T e, Ptr p = nullptr, Ptr s = nullptr)
		: data(e), pred(p), succ(s)
	{}

	Ptr insert_as_pred(T const& e) {
		auto pos = new ListNode<T>(e, pred, this);
		pred->succ = pos;
		pred = pos;
		return pos;
	}

	Ptr insert_as_succ(T const& e) {
		auto pos = new ListNode<T>(e, this, succ);
		succ->pred = pos;
		succ = pos;
		return pos;
	}
};
