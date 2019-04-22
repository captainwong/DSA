#pragma once

#include "entry.h"

//! 四联表节点
template <typename T>
struct QuadlistNode
{
	typedef QuadlistNode<T> Node;
	typedef Node* Ptr;

	//! 所存词条
	T entry;
	//! 前驱
	Ptr pred;
	//! 后继
	Ptr succ;
	//! 上邻
	Ptr above;
	//! 下邻
	Ptr below;

	QuadlistNode(T entry = T(), Ptr pred = nullptr, Ptr succ = nullptr, Ptr above = nullptr, Ptr below = nullptr)
		: entry(entry)
		, pred(pred)
		, succ(succ)
		, above(above)
		, below(below)
	{}

	//! 插入新节点，以当前节点为前驱，以节点b为下邻
	Ptr insertAsSuccAbove(T const& e, Ptr b = nullptr) {
		auto x = new Node(e, this, succ, nullptr, b);
		succ->pred = x; succ = x;
		if (b) { b->above = x; }
		return x;
	}
};
