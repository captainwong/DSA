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

	//! ����
	virtual NodePtr& search(const T& e) { return searchIn(this->root_, e, hot_ = nullptr); }
	
	//! ����
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
		auto w = x; // ʵ�ʱ�ժ���Ľڵ㣬��ֵͬx
		NodePtr succ = nullptr; // ʵ�ʱ�ժ���Ľڵ�Ľ�����
		if (!x->lChild) { // ������Ϊ��
			succ = x = x->rChild_; // ������Ϊ��������������Ϊ�գ�
		} else if (!x->rChild) { // ������Ϊ��
			succ = x = x->lChild_; // ������Ϊ�����ӣ�����Ϊ�գ�
		} else { // ����������������
			w = w->succ(); std::swap(x->data_, w->data_); // ��x������w��������
			auto u = w->parent_;
			(u == x ? u->rChild_ : u->lChild_) = succ = w->rChild_;
		}

		hot = w->parent_; // ��¼ʵ�ʱ�ɾ���ڵ㸸��
		if (succ) { succ->parent_ = hot; } // ����ɾ���ڵ�Ľ�������hot����
		// todo �ͷű�ժ���Ľڵ� release(w->data); release(w);
		return succ; // ���ؽ�����
	}

	//! ɾ��
	virtual bool remove(const T& e) {
		auto& x = search(e);
		if (!x) { return false; }
		removeAt(x, hot_);
		this->size_--;
		updateHeightAbove(x);
		return true;
	}

protected:
	//! ���нڵ�ĸ���
	NodePtr hot_;

	//! 3 + 4 �ع�
	NodePtr connect34(
		NodePtr, NodePtr, NodePtr,
		NodePtr, NodePtr, NodePtr, NodePtr
	);

	//! ��ת����
	NodePtr rotateAt(NodePtr);


};