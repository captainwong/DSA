#pragma once

#include "vector.h"

//! B-树节点
template <typename T>
struct BTNode
{
	typedef BTNode<T>* Ptr;

	//! 父节点
	Ptr parent_;
	//! 关键码
	Vector<T> key_;
	//! 孩子（长度总比key多1）
	Vector<Ptr> child_;

	BTNode() { parent_ = nullptr; child_.insert(0, nullptr); }

	BTNode(T const& e, Ptr lc = nullptr, Ptr rc = nullptr) {
		parent_ = nullptr; key_.insert(0, e);
		child_.insert(0, lc); child_.insert(1, rc);
		if (lc) { lc->parent_ = this; } 
		if (rc) { rc->parent_ = this; }
	}
};