#pragma once
#include "../../05.bintree/bintree/BinTree.h"

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
	static NodePtr& searchIn(NodePtr& v, const T& e, NodePtr & hot) {
		if (!v || (e == v->data)) { return v; }
		hot = v;
		return searchIn(((e < v->data) ? v->lChild : v->rChild), e, hot);
	}

	//! 查找
	virtual NodePtr& search(const T& e) { return searchIn(root_, e, hot_ = nullptr); }
	
	//! 插入
	virtual NodePtr insert(const T& e) {
		auto& x = search(e);
		if (!x) {
			x = new Node(e, hot_);
			size_++;
			updateHeightAbove(x);
		}
		return x;
	}

	static NodePtr removeAt(NodePtr& x, NodePtr& hot) {
		auto w = x;
		NodePtr succ = nullptr;
		if (!x->lChild) {
			succ = x = x->rChild;
		} else if (!x->rChild) {
			succ = x = x->lChild;
		} else {

		}

	}

	//! 删除
	virtual bool remove(const T& e) {
		auto& x = search(e);
		if (!x) { return false; }
		removeAt(x, hot_);
		size_--;
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