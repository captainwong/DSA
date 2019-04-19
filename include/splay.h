#pragma once

#include "bst.h"

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
					g->attachAsLChild(p->rChild_);
					p->attachAsLChild(v->rChild_);
					p->attachAsRChild(g);
					v->attachAsRChild(p);
				} else { // zig-zag
					g->attachAsRChild(v->lChild_);
					p->attachAsLChild(v->rChild_);
					v->attachAsLChild(g);
					v->attachAsRChild(p);
				}
			} else {
				if (p->isRChild()) { // zag-zag
					g->attachAsRChild(p->lChild_);
					p->attachAsRChild(v->lChild_);
					p->attachAsLChild(g);
					v->attachAsLChild(p);
				} else { // zag-zig
					p->attachAsRChild(v->lChild_);
					g->attachAsRChild(v->rChild_);
					v->attachAsLChild(p);
					v->attachAsRChild(g);
				}
			}

			// 若无曾祖父gg，则v现在就是树根；否则，gg此后应以v为左或右孩子
			if (!gg) {  v->parent_ = nullptr;
			} else { (g == gg->lChild_) ? gg->attachAsLChild(v) : gg->attachAsRChild(v); }

			this->updateHeight(g);
			this->updateHeight(p);
			this->updateHeight(v);

		} // 双层伸展结束时，必有 g==nullptr, 但p可能非空

		// 若p果真是根，只需再额外单旋（至多一次）
		if (p = v->parent_) {
			if (v == p->lChild_) {
				p->attachAsLChild(v->rChild_);
				v->attachAsRChild(p);
			} else {
				p->attachAsRChild(v->lChild_);
				v->attachAsLChild(p);
			}

			this->updateHeight(p);
			this->updateHeight(v);
		}

		// 伸展完成，返回树根
		v->parent_ = nullptr;
		return v;
	}

public:
	//! 查找
	virtual NodePtr& search(const T& e) override {
		// 调用标准BST的内部接口定位目标节点
		auto p = this->searchIn(this->root_, e, this->hot_ = nullptr);

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
				t->lChild_->parent_ = this->root_;
				t->lChild_ = nullptr;
			}
		}

		this->updateHeightAbove(t); // 更新t及其祖先（实际上只有root_一个）的高度
		return this->root_; //新节点必然置于树根，返回之
	} // 无论e是否存在于原树中，返回时总有root_->data == e

	//! 删除
	bool remove(const T& e) override {
		// 若树空或目标不存在，则无法删除
		if (!this->root_ || e != search(e)->data_) { return false; }

		// 经search()后节点e已被伸展至树根
		auto t = this->root_;

		if (!this->root_->hasLChild()) { // 若无左子树，直接删除
			this->root_ = this->root_->rChild_; // 以右子树为树根
			if (this->root_) { this->root_->parent_ = nullptr; } // 更新右子树父节点为null
		} else if (!this->root_->hasRChild()) { // 若无右子树，直接删除
			this->root_ = this->root_->lChild_; // 以左子树为树根
			if (this->root_) { this->root_->parent_ = nullptr; } // 更新左子树父节点为null
		} else { // 左、右子树同时存在
			// 暂时切除左子树
			auto ltree = this->root_->lChild_;
			ltree->parent_ = nullptr;
			this->root_->lChild_ = nullptr;

			// 只保留右子树
			this->root_ = this->root_->rChild_;
			this->root_->parent_ = nullptr;
			
			// 以原树根为目标，做一次（必定失败的）查找
			search(t->data_);

			// 至此，右子树中最小节点必伸展至根，且（因无雷同节点）其左子树必空，于是只需将原左子树接回原位即可
			this->root_->lChild_ = ltree;
			ltree->parent_ = this->root_;
		}

		// 释放节点，更新规模
		//release(t->data_); release(t); 
		this->size_--;

		// 此后，若树非空，则树根的高度需要更新
		if (this->root_) {
			this->updateHeight(this->root_);
		}

		return true;
	}
};
