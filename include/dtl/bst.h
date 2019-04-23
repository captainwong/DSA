#pragma once

#include "bintree.h"
#include "swap.h"

namespace dtl
{

template <typename K, typename V>
struct Entry
{
	K key;
	V value;

	typedef typename Entry<K, V> EntryType;

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
	typedef typename BinNode<T> Node;
	typedef typename Node::Ptr NodePtr;

	static NodePtr& searchIn(NodePtr& v, const T& e, NodePtr & hot) {
		if (!v || (e == v->data_)) { return v; }
		hot = v;
		return searchIn(((e < v->data_) ? v->lChild_ : v->rChild_), e, hot);
	}

	//! 查找
	virtual NodePtr& search(const T& e) { return searchIn(this->root_, e, this->hot_ = nullptr); }

	//! 插入
	virtual NodePtr insert(const T& e) {
		auto& x = search(e);
		if (!x) {
			x = new Node(e, this->hot_);
			this->size_++;
			this->updateHeightAbove(x);
		}
		return x;
	}

	static NodePtr removeAt(NodePtr& x, NodePtr& hot) {
		NodePtr w = x; // 实际被摘除的节点，初值同x
		NodePtr succ = nullptr; // 实际被摘除的节点的接替者
		if (!x->lChild_) { // 左子树为空
			succ = x = x->rChild_; // 接替者为其右子树（可能为空）
		} else if (!x->rChild_) { // 右子树为空
			succ = x = x->lChild_; // 接替者为其左孩子（可能为空）
		} else { // 左右子树并存的情况
			w = w->succ(); swap(x->data_, w->data_); // 令x与其后继w互换数据
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
		removeAt(x, this->hot_);
		this->size_--;
		this->updateHeightAbove(x);
		return true;
	}

protected:
	//! 命中节点的父亲
	NodePtr hot_;

	//! 3 + 4 重构
	NodePtr connect34(NodePtr a, NodePtr b, NodePtr c,
					  NodePtr t0, NodePtr t1, NodePtr t2, NodePtr t3) {
		a->lChild_ = t0; if (t0) { t0->parent_ = a; }
		a->rChild_ = t1; if (t1) { t1->parent_ = a; }
		this->updateHeight(a);

		c->lChild_ = t2; if (t2) { t2->parent_ = c; }
		c->rChild_ = t3; if (t3) { t3->parent_ = c; }
		this->updateHeight(c);

		b->lChild_ = a; a->parent_ = b;
		b->rChild_ = c; c->parent_ = b;
		this->updateHeight(b);

		return b; // 该子树新的根节点
	}

	//! 旋转调整
	NodePtr rotateAt(NodePtr v) {
		auto p = v->parent_;
		auto g = p->parent_;

		if (p->isLChild()) { // zig
			if (v->isLChild()) { // zig-zig
				p->parent_ = g->parent_; // 向上联接
				return connect34(v, p, g,
								 v->lChild_, v->rChild_, p->rChild_, g->rChild_);
			} else { // zig-zag
				v->parent_ = g->parent_; // 向上联接
				return connect34(p, v, g,
								 p->lChild_, v->lChild_, v->rChild_, g->rChild_);
			}
		} else { // zag
			if (v->isRChild()) { // zag-zag
				p->parent_ = g->parent_; //向上联接
				return connect34(g, p, v,
								 g->lChild_, p->lChild_, v->lChild_, v->rChild_);
			} else { // zag-zig
				v->parent_ = g->parent_; //向上联接
				return connect34(g, v, p,
								 g->lChild_, v->lChild_, v->rChild_, p->rChild_);
			}
		}
	}
};

}
