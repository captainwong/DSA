#pragma once
#include "../../05.bintree/bintree/BinTree.h"
#include <algorithm>

template <typename K, typename V>
struct Entry
{
	K key;
	V value;

	using EntryType = typename Entry<K, V>;

	Entry(K k = K(), V v = V())
		: key(k)
		, value(v)
	{}

	Entry(EntryType const & e)
		: key(e.key)
		, value(e.value)
	{}

	bool operator < (const EntryType & e) { return key < e.key; }
	bool operator > (const EntryType & e) { return key > e.key; }
	bool operator == (const EntryType & e) { return key == e.key; }
	bool operator != (const EntryType & e) { return key != e.key; }
};

template <typename T> 
class BST : public BinTree<T>
{
public:
	using Node = typename BinNode<T>;
	using NodePtr = typename Node::Ptr;

	static NodePtr& searchIn(NodePtr& v, const T& e, NodePtr & hot) {
		if (!v || (e == v->data_)) { return v; }
		hot = v;
		return searchIn(((e < v->data_) ? v->lChild_ : v->rChild_), e, hot);
	}

	//! 查找
	virtual NodePtr& search(const T& e) { return searchIn(this->root_, e, hot_ = nullptr); }
	
	//! 插入
	virtual NodePtr insert(const T& e) {
		auto& x = search(e);
		if (!x) {
			x = new Node(e, hot_);
			this->size_++;
			updateHeightAbove(x);
		}
		return x;
	}

	static NodePtr removeAt(NodePtr& x, NodePtr& hot) {
		auto w = x; // 实际被摘除的节点，初值同x
		NodePtr succ = nullptr; // 实际被摘除的节点的接替者
		if (!x->lChild) { // 左子树为空
			succ = x = x->rChild_; // 接替者为其右子树（可能为空）
		} else if (!x->rChild) { // 右子树为空
			succ = x = x->lChild_; // 接替者为其左孩子（可能为空）
		} else { // 左右子树并存的情况
			w = w->succ(); std::swap(x->data_, w->data_); // 令x与其后继w互换数据
			auto u = w->parent_;
			(u == x ? u->rChild_ : u->lChild_) = succ = w->rChild_;
		}

		hot = w->parent_; // 记录实际被删除节点父亲
		if (succ) { succ->parent_ = hot; } // 将被删除节点的接替者与hot相联
		// todo 释放被摘除的节点 release(w->data); release(w);
		return succ; // 返回接替者
	}

	//! 删除
	virtual bool remove(const T& e) {
		auto& x = search(e);
		if (!x) { return false; }
		removeAt(x, hot_);
		this->size_--;
		updateHeightAbove(x);
		return true;
	}

protected:
	//! 命中节点的父亲
	NodePtr hot_;

	//! 3 + 4 重构
	NodePtr connect34(
		NodePtr, NodePtr, NodePtr,
		NodePtr, NodePtr, NodePtr, NodePtr
	);

	//! 旋转调整
	NodePtr rotateAt(NodePtr);


};