#pragma once

#include "bst.h"

template <typename T>
class RBTree : public BST<T>
{
public:
	typedef BinNode<T> Node;
	typedef Node* NodePtr;

	//! 插入重写
	virtual NodePtr insert(const T& e) override {
		auto& x = this->search(e); if (x) { return x; }
		x = new Node(e, this->hot_, nullptr, nullptr, -1, RBColor::RB_RED);
		solveDoubleRed(x); return x ? x : this->hot_->parent_;
	}

	//! 删除重写
	virtual bool remove(const T& e) override {
		auto& x = this->search(e); if (!x) { return false; }
		auto r = this->removeAt(x, this->hot_); if (!(--this->size_)) { return true; }
		// hot_某一孩子刚被删除，且被r所指节点（可能是nullptr）接替。以下检查是否失衡，并做必要调整
		if (!this->hot_) { // 若刚被删除的是根节点，则将其置黑，并更新黑高度
			this->root_->color_ = RBColor::RB_BLACK; this->updateHeight(this->root_); return true;
		}
		// 以下，原x（现r）必非根，_hot必非空
		if (blackHeightUpdated(this->hot_)) { return true; } // 若所有祖先的黑深度依然平衡，则无需调整
		if (isRed(r)) { r->color_ = RBColor::RB_RED; r->height_++; return true; } // 否则，若r为红，则只需令其转黑
		// 以下，原x（现r）均为黑色
		solveDoubleBlack(r); return true;
	}

protected:
	/*
	* @brief 双红修正
	* @note RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
	*	RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
	*	RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
	*/
	void solveDoubleRed(NodePtr x) { // x当前必为红
		// 若已（递归）转至树根，则将其转黑，整树黑高度也随之递增
		if (x->isRoot()) { this->root_->color_ = RBColor::RB_BLACK; this->root_->height_++; return; }
		// 否则，x的父亲p必存在
		auto p = x->parent_; if (isBlack(p)) { return; } // 若p为黑，则可终止调整。否则
		auto g = p->parent_; // 既然p为红，则x的祖父必存在，且必为黑色
		auto u = x->uncle(); // 以下，视x叔父u的颜色分别处理		
		if (isBlack(u)) { // RR-1: u为黑色（含nullptr）时
			if (x->isLChild() == p->isLChild()) { // 若x与p同侧（即zIg-zIg或zAg-zAg），则
				p->color_ = RBColor::RB_BLACK; // p由红转黑，x保持红
			} else { // 若x与p异侧（即zIg-zAg或zAg-zIg），则
				x->color_ = RBColor::RB_BLACK; // x由红转黑，p保持红
			}
			g->color_ = RBColor::RB_RED; // g必定由黑转红
			// todo 以上虽保证总共两次染色，但因增加了判断而得不偿失
			// 在旋转后将根置黑、孩子置红，虽需三次染色但效率更高
			auto gg = g->parent_;
			auto r = this->fromParentTo(g) = this->rotateAt(x); // 调整后的子树根节点
			r->parent_ = gg; // 与原曾祖父联接
		} else { // RR-2: u为红色
			p->color_ = RBColor::RB_BLACK; p->height_++; // p由红转黑
			u->color_ = RBColor::RB_BLACK; u->height_++; // u由红转黑
			if (!g->isRoot()) { g->color_ = RBColor::RB_RED; } // g若非根，则转红
			solveDoubleRed(g); // todo 继续调整g（类似于尾递归，可优化为迭代形式）
		}
	}

	/*
	* @brief 双黑修正
	* @note RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
	*   分为三大类共四种情况：
	*	BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
	*	BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
	*	BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
	*	BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
	*/
	void solveDoubleBlack(NodePtr r) {
		auto p = r ? r->parent_ : this->hot_; if (!p) { return; }
		auto s = r->sibling();
		if (isBlack(s)) { // 兄弟s为黑色
			// s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
			auto t = isRed(s->lChild_) ? s->lChild_ : (isRed(s->rChild_) ? s->rChild_ : nullptr);
			if (t) { // BB-1: 黑s有红孩子
				auto oldColor = p->color_; // 备份原子树根节点p颜色，并对t及其父亲、祖父
				// 以下，通过旋转重平衡，并将新子树的左、右孩子染黑
				auto b = this->fromParentTo(p) = this->rotateAt(t); // 旋转
				if (b->lChild_) { b->lChild_->color_ = RBColor::RB_BLACK; this->updateHeight(b->lChild_); }
				if (b->rChild_) { b->rChild_->color_ = RBColor::RB_BLACK; this->updateHeight(b->rChild_); }
				b->color_ = oldColor; this->updateHeight(b); // 新子树根节点继承原根节点的颜色
			} else { // 黑s无红孩子
				s->color_ = RBColor::RB_RED; s->height_--; // s转红
				if (isRed(p)) { // BB-2R
					p->color_ = RBColor::RB_BLACK; // p转黑，但黑高度不变
				} else { // BB-2B
					p->height_--; // p保持黑，但黑高度下降
					solveDoubleBlack(p); // 递归上溯
				}
			}
		} else { // BB-3: 兄弟s为红
			s->color_ = RBColor::RB_BLACK; p->color_ = RBColor::RB_RED; // s转黑，p转红
			auto t = s->isLChild() ? s->lChild_ : s->rChild_; // 取t与其父s同侧
			this->hot_ = p; this->fromParentTo(p) = this->rotateAt(t); // 对t及其父亲、祖父做平衡调整
			solveDoubleBlack(r); // 继续修正r处双黑 —— 此时的p已转红，故后续只能是BB-1或BB-2R
		}
	}

	//! 更新节点高度重写
	virtual int updateHeight(NodePtr node) override {
		// 孩子一般黑高度相等，除非出现双黑
		// 红黑树中各节点左、右孩子的黑高度通常相等
		// 这里之所以取更大值，是便于在删除节点后的平衡调整过程中，正确更新被删除节点父亲的黑高度
		// 否则，rotateAt()会根据被删除节点的替代者（高度小一）设置父节点的黑高度
		node->height_ = stature(node->lChild_) < stature(node->rChild_) ? stature(node->rChild_) : stature(node->lChild_);
		return isBlack(node) ? node->height_++ : node->height_; // 若当前节点为黑，则计入黑深度
		// 因统一定义stature(nullptr) = -1，故height比黑高度少一，好在不致影响到各种算法中的比较判断
	}
};