#pragma once

#include "bst.h"

namespace dtl
{

template <typename T>
class AVL : public BST<T>
{
public:
	typedef typename BinNode<T> Node;
	typedef typename Node::Ptr NodePtr;

	virtual NodePtr insert(T const& e) override {
		auto& x = this->search(e); if (x) { return x; }

		x = new Node(e, this->hot_);
		this->size_++;
		auto xx = x;

		// 从x的父亲出发逐层向上，一次检查各代祖先g
		for (auto g = x->parent_; g; g = g->parent_) {
			if (!avlBalanced(g)) { // 一旦发现g失衡，则通过调整恢复平衡
				this->fromParentTo(g) = this->rotateAt(tallerChild(tallerChild(g)));
				break; // g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整结束
			} else { // 否则（在依然平衡的祖先处），只需简单滴
				this->updateHeight(g); // 更新其高度（平衡性虽不变，高度却可能改变）
			}
		}

		return xx; // 返回新节点：至多只需一次调整
	}

	virtual bool remove(T const& e) override {
		auto& x = this->search(e); if (!x) { return false; }
		this->removeAt(x, this->hot_); this->size_--; // 在按照BST规则删除之后，hot_及其祖先均有可能失衡

		// 从hot_（被删除节点的父亲）出发，依次检查各代祖先g
		for (auto g = this->hot_; g; g = g->parent_) {
			if (!avlBalanced(g)) {
				g = this->fromParentTo(g) = this->rotateAt(tallerChild(tallerChild(g)));
			}
			this->updateHeight(g);
		} // 可能需做过Ω(log n)次调整；无论是否做过调整，全树高度均可能下降

		return true;
	}
};

}
