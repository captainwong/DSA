#pragma once

#include "../../07.bst/bst/bst.h"

//! 在节点*p与*lc（可能为空）之间建立父（左）子关系
template <typename NodePtr> inline
void attachAsLChild(NodePtr p, NodePtr lc) { p->lChild = lc; if (lc) { lc->parent = p; } }

//! 在节点*p与*rc（可能为空）之间建立父（右）子关系
template <typename NodePtr> inline
void attachAsRChild(NodePtr p, NodePtr rc) { p->rChild = rc; if (rc) { rc->parent = p; } }


//! 伸展树
template <typename T>
class Splay : public BST<T>
{
public:
	typedef typename BinNode<T> Node;
	typedef typename Node::Ptr NodePtr;

protected:

	//! 将v伸展至根
	NodePtr splay(NodePtr v) {
		if (!v) { return nullptr; }
		NodePtr p, g;
		while ((p = v->parent_) && (g = p->parent_)) {
			auto gg = g->parent_; // 每轮之后，v都将以原曾祖父为父
			if (v->isLChild()) {
				if (p->isLChild()) { // zig-zig
					attachAsLChild(g, p->rChild_);
					attachAsLChild(p, v->rChild_);
					attachAsRChild(p, g);
					attachAsRChild(v, p);
				} else { // zig-zag
					attachAsRChild(g, v->lChild_);
					attachAsLChild(p, v->rChild_);
					attachAsLChild(v, g);
					attachAsRChild(v, p);
				}
			} else {
				if (p->isRChild()) { // zag-zag
					attachAsRChild(g, p->lChild_);
					attachAsRChild(p, v->lChild_);
					attachAsLChild(p, g);
					attachAsLChild(v, p);
				} else { // zag-zig
					attachAsRChild(p, v->lChild_);
					attachAsRChild(g, v->rChild_);
					attachAsLChild(v, p);
					attachAsRChild(v, g);
				}
			}

			// 若无曾祖父gg，则v现在就是树根；否则，gg此后应以v为左或右孩子
			if (!gg) { 
				v->parent_ = nullptr;
			} else {
				(g == gg->lChild_) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
			}

			updateHeight(g);
			updateHeight(p);
			updateHeight(v);

		} // 双层伸展结束时，必有 g==nullptr, 但p可能非空

		// 若p果真是根，只需再额外单旋（至多一次）
		if (p = v->parent_) {
			if (v == p->lChild_) {
				attachAsLChild(p, v->rChild_);
				attachAsRChild(v, p);
			} else {
				attachAsRChild(p, v->lChild_);
				attachAsLChild(v, p);
			}

			updateHeight(p);
			updateHeight(v);
		}

		// 伸展完成，返回树根
		v->parent_ = nullptr;
		return v;
	}

public:
	//! 查找
	virtual NodePtr& search(const T& e) override {
		// 调用标准BST的内部接口定位目标节点
		auto p = searchIn(this->root_, e, this->hot_ = nullptr);

		// 无论成功与否，最后被访问的节点都将伸展至根
		this->root_ = splay(p ? p : this->hot_);

		//总是返回根节点
		return this->root_;
	}

	//! 插入
	virtual NodePtr insert(const T& e) override {
		// 处理原树为空树的退化情况
		if (!this->root_) {
			this->size_++;
			return this->root_ = new Node(e);
		}

		// 处理节点已存在的情况
		if (e == search(e)->data_) {
			return this->root_; // 查找操作时已经伸展
		} // 隐含了else，此时查找失败，但root_已经更新为适合插入的父节点

		this->size_++;
		auto t = this->root_;

		if (this->root_->data_ < e) {
			this->root_ = new Node(e, nullptr, t, t->rChild_);
			t->parent_ = this->root_;
			if (t->rChild_) {
				t->rChild_->parent_ = this->root_;
				t->rChild_ = nullptr;
			}
		} else {
			this->root_ = new Node(e, nullptr, t->lChild_, t);
			t->parent_ = this->root_;
			if (t->lChild_) {
				t->lChild_->parent = this->root_;
				t->lChild_ = nullptr;
			}
		}

		updateHeightAbove(t); // 更新t及其祖先（实际上只有root_一个）的高度
		return this->root_; //新节点必然置于树根，返回之
	} // 无论e是否存在于原树中，返回时总有root_->data == e

	//! 删除
	bool remove(const T& e) override {

	}
};
