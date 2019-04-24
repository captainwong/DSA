#pragma once

#include "BinNode.h"
#include "release.h"

namespace dtl
{

/************辅助函数************/
//! 删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template <typename T>
static int removeAt(BinNode<T>* x)
{
	if (!x) { return 0; }
	int n = 1 + removeAt(x->lChild_) + removeAt(x->rChild_);
	release(x->data_); release(x);
	return n;
}

template <typename T>
class BinTree
{
public:
	typedef BinNode<T> Node;
	typedef Node* NodePtr;
	typedef BinTree<T> BinTreeType;
	typedef BinTreeType* BinTreePtr;

protected:
	int size_;
	NodePtr root_;

	//! 更新节点 node 的高度
	virtual int updateHeight(NodePtr node) {
		// return node->height_ = 1 + std::max(stature(node->lChild_), stature(node->rChild_));
		auto lh = stature(node->lChild_); 
		auto rh = stature(node->rChild_);
		return node->height_ = 1 + (lh < rh ? rh : lh);
	}

	//! 更新节点 node 及其祖先的高度
	void updateHeightAbove(NodePtr node) {
		while (node) { 
			updateHeight(node); 
			node = node->parent_; 
		}
	}

public:
	BinTree()
		: size_(0)
		, root_(nullptr)
	{}

	int size() const { return size_; }
	bool empty() const { return !root_; }
	NodePtr root() const { return root_; }



	/*******************************************mutable*****************************************/

	//! 来自父亲的引用
	NodePtr& fromParentTo(NodePtr node) {
		return node->isRoot() ? root_ : (node->isLChild() ? node->parent_->lChild_ : node->parent_->rChild_);
	}

	//! 插入根节点
	NodePtr insertAsRootNode(T const& data) { size_ = 1; return (root_ = new Node(data)); }

	//! e作为x的左孩子（原无）插入
	NodePtr insertAsLeftChild(NodePtr node, T const& data) {
		size_++; 
		node->insertAsLeftChild(data); 
		updateHeightAbove(node);
		return node->lChild_;
	}

	//! e作为x的右孩子（原无）插入
	NodePtr insertAsRightChild(NodePtr node, T const& data) {
		size_++; 
		node->insertAsRightChild(data); 
		updateHeightAbove(node);
		return node->rChild_;
	}

	//! lc作为x的左子树接入, lc本身置空
	NodePtr attachAsLChild(NodePtr x, BinTreePtr& lc) {
		if (x->lChild_ = lc->root_) { x->lChild_->parent_ = x; }
		size_ += lc->size_; 
		updateHeightAbove(x);
		lc->root_ = nullptr; lc->size_ = 0; release(lc); lc = nullptr;
		return x;
	}

	//! rc作为x的右子树接入，rc本身置空
	NodePtr attachAsRChild(NodePtr x, BinTreePtr& rc) {
		if (x->rChild_ = rc->root_) { x->rChild_->parent_ = x; }
		size_ += rc->size_;
		updateHeightAbove(x);
		rc->root_ = nullptr; rc->size_ = 0; release(rc); rc = nullptr;
		return x;
	}

	//! 删除以位置x处节点为根的子树，返回该子树原先的规模
	int remove(NodePtr x) {
		fromParentTo(x) = nullptr; // 切断来自父节点的指针
		updateHeightAbove(x->parent_); // 更新祖先高度
		int n = removeAt(x); size_ -= n;
		return n;
	}

	//! 将子树x从当前树中摘除，并将其转换为一棵独立子树
	BinTreePtr secede(NodePtr x) {
		fromParentTo(x) = nullptr;
		updateHeightAbove(x->parent_);
		auto tree = new BinTreeType();
		x->parent_ = nullptr;
		tree->root_ = x;
		tree->size_ = x->size();
		size_ -= tree->size_;
		return tree;
	}


	/*************************************traverse**************************************/

	

	//! 先序遍历
	template <typename VST>
	void travPreOrder(VST& visit) {
		
	}

	

	//! 中序遍历
	template <typename VST>
	void travInOrder(VST& visit) {
		
	}

	//! 后序遍历
	template <typename VST>
	void travPostOrder(VST& visit) {
		
	}

	//! 层次遍历
	template <typename VST>
	void travLevelOrder(VST& visit) {
		
	}
};

}
