#pragma once

#include "stack.h"
#include "queue.h"

namespace dtl
{

enum class RBColor {
	RB_RED,
	RB_BLACK,
};

template <typename T>
struct BinNode
{
	typedef BinNode<T>* Ptr;

	T data_;
	Ptr parent_;
	Ptr lChild_;
	Ptr rChild_;
	int height_;

	//! 红黑树使用
	RBColor color_;

	BinNode()
		: data_()
		, parent_(nullptr)
		, lChild_(nullptr)
		, rChild_(nullptr)
		, height_(-1)
		, color_(RBColor::RB_RED)
	{}

	BinNode(const T& data, Ptr parent = nullptr, Ptr lChild = nullptr, Ptr rChild = nullptr, int height = 0, RBColor color = RBColor::RB_RED)
		: data_(data)
		, parent_(parent)
		, lChild_(lChild)
		, rChild_(rChild)
		, height_(height)
		, color_(color)
	{}

	int size() const {
		int s = 1;
		if (lChild_) { s += lChild_->size(); }
		if (rChild_) { s += rChild_->size(); }
		return s;
	}

	bool operator<(const BinNode& rhs) { return this->data_ < rhs.data_; }
	bool operator>(const BinNode& rhs) { return this->data_ > rhs.data_; }
	bool operator==(const BinNode& rhs) { return this->data_ == rhs.data_; }
	bool operator!=(const BinNode& rhs) { return this->data_ != rhs.data_; }
	
	inline bool isRoot() const { return !parent_; }
	inline bool isLChild() const { return parent_ && parent_->lChild_ == this; }
	inline bool isRChild() const { return parent_ && parent_->rChild_ == this; }
	inline bool hasParent() const { return parent_; }
	inline bool hasLChild() const { return lChild_; }
	inline bool hasRChild() const { return rChild_; }
	inline bool hasChild() const { return lChild_ || rChild_; }
	inline bool hasBothChild() const { return lChild_ && rChild_; }
	inline bool isLeaf() const { return !lChild_ && !rChild_; }
	inline Ptr sibling() const { return isLChild() ? parent_->rChild_ : parent_->lChild_; }
	inline Ptr uncle() const { return parent_->isLChild() ? parent_->parent_->rChild_ : parent_->parent_->lChild_; }

	Ptr insertAsLeftChild(const T& data) { return (lChild_ = new BinNode(data, this)); }
	Ptr insertAsRightChild(const T& data) { return (rChild_ = new BinNode(data, this)); }	

	//! 定位节点v的直接后继
	Ptr succ() {
		auto s = this; // 记录后继的临时变量
		if (rChild_) { // 若有右孩子，则直接后继必在右子树中，具体地就是
			s = rChild_; // 右子树中
			while (s->lChild_) {  s = s->lChild_; } // 最靠左（最小）的节点
		} else { // 否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
			while (s->isRChild()) { s = s->parent_; } // 逆向地沿右向分支，不断朝左上方移动
			s = s->parent_; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
		}
		return s;
	}

	//! 与lc（可能为空）之间建立父（左）子关系
	void attachAsLChild(Ptr lc) { lChild_ = lc; if (lc) { lc->parent_ = this; } }

	//! 与rc（可能为空）之间建立父（右）子关系
	void attachAsRChild(Ptr rc) { rChild_ = rc; if (rc) { rc->parent_ = this; } }

	/*****************traverse*******************/

	//! 先序遍历算法（迭代版#1）
	template <typename VST>
	void travPre_I1(VST& visit) {
		Stack<Ptr> s;
		s.push(this);
		while (!s.empty()) {
			auto x = s.pop();
			visit(x->data_);
			if (x->rChild_) { s.push(x->rChild_); }
			if (x->lChild_) { s.push(x->lChild_); }
		}
	}

	//! 先序遍历算法（迭代版#2）
	template <typename VST>
	void travPre_I2(VST& visit) {
		Stack<Ptr> s;
		auto x = this;
		while (true) {
			visitAlongLeftBranch(x, visit, s);
			if (s.empty()) { break; }
			x = s.pop();
		}
	}

	//! 先序遍历算法（递归版）
	template <typename VST>
	void travPre_R(VST& visit) {
		visitTravPre(this, visit);
	}

	//! 中序遍历算法（迭代版#1）
	template <typename VST>
	void travIn_I1(VST& visit) {
		Stack<Ptr> s;
		auto x = this;
		while (true) {
			goAlongLeftBranch(x, s);
			if (s.empty()) { break; }
			x = s.pop(); 
			visit(x->data_);
			x = x->rChild_;
		}
	}

	//! 中序遍历算法（迭代版#2）
	template <typename VST>
	void travIn_I2(VST& visit) {
		Stack<Ptr> s;
		auto x = this;
		while (true) {
			if (x) {
				s.push(x);
				x = x->lChild_;
			} else if (!s.empty()) {
				x = s.pop();
				visit(x->data_);
				x = x->rChild_;
			} else { break; }
		}
	}

	//! 中序遍历算法（迭代版#3，无需辅助栈）
	template <typename VST>
	void travIn_I3(VST& visit) {

	}
};


/***********************一些辅助模板函数***************************/

//! 从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST>
static void visitAlongLeftBranch(typename BinNode<T>::Ptr node, VST& visit, Stack<typename BinNode<T>::Ptr>& stack)
{
	while (node) {
		visit(node->data_);
		stack.push(node->rChild_);
		node = node->lChild_;
	}
}

//! 先序遍历算法（递归版）辅助递归函数
template <typename T, typename VST>
static void visitTravPre(typename BinNode<T>::Ptr node, VST& visit)
{
	if (!node) { return; }
	visit(node->data_);
	visitTravPre(node->lChild_);
	visitTravPre(node->rChild_);
}

//! 中序遍历算法（迭代版#1）辅助函数，从当前节点出发，沿左分支不断深入，直至没有左分支的节点
template <typename T>
static void goAlongLeftBranch(typename BinNode<T>::Ptr node, Stack<typename BinNode<T>::Ptr>& stack)
{
	while (node) {
		stack.push(node);
		node = node->lChild_;
	}
}

//! 节点高度
template <typename T>
int stature(BinNode<T>* node)
{
	return node ? node->height_ : -1;
}

//! 理想平衡
template <typename T>
bool balanced(BinNode<T>* node)
{
	return stature(node->lChild_) == stature(node->rChild_);
}

//! 平衡因子
template <typename T>
int balanceFactor(BinNode<T>* node)
{
	return stature(node->lChild_) - stature(node->rChild_);
}

//! AVL 平衡
template <typename T>
bool avlBalanced(BinNode<T>* node)
{
	auto factor = balanceFactor(node);
	return (-2 < factor) && (factor < 2);
}

//! 在左、右孩子中取更高者
// 在AVL平衡调整前，借此确定重构方案
template <typename T>
BinNode<T>* tallerChild(BinNode<T>* node)
{
	return 
	stature(node->lChild_) > stature(node->rChild_) ? node->lChild_ : ( // 左高
		stature(node->lChild_) < stature(node->rChild_) ? node->rChild_ : ( // 右高
			node->isLChild() ? node->lChild_ : node->rChild_)); // 等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先
}

//! 红黑树节点判黑
template <typename T>
bool isBlack(BinNode<T>* node)
{
	return !node || (RBColor::RB_BLACK == node->color_); // 外部节点也视作黑节点
}

//! 红黑树节点判红
template <typename T>
bool isRed(BinNode<T>* node)
{
	return !isBlack(node); // 非黑即红
}

//! 红黑树高度更新条件
template <typename T>
bool blackHeightUpdated(BinNode<T>* node)
{
	return (stature(node->lChild_) == stature(node->rChild_))
		&& (node->height_ == (isRed(node) ? stature(node->lChild_) : stature(node->lChild_) + 1));
}

}
