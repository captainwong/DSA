#pragma once

template <typename T>
struct BinNode
{
	typedef typename BinNode<T>* Ptr;

	T data_;
	Ptr parent_;
	Ptr lChild_;
	Ptr rChild_;
	int height_;

	BinNode()
		: data_()
		, parent_(nullptr)
		, lChild_(nullptr)
		, rChild_(nullptr)
		, height_(-1)
	{}

	BinNode(const T& data, Ptr parent = nullptr, Ptr lChild = nullptr, Ptr rChild = nullptr)
		: data_(data)
		, parent_(parent)
		, lChild_(lChild)
		, rChild_(rChild)
		, height_(0)
	{}

	int size() const {
		int s = 1;
		if (lChild_) { s += lChild_->size(); }
		if (rChild_) { s += rChild_->size(); }
		return s;
	}
	
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

	Ptr insertAsLeftChild(const T& data) {
		return (lChild_ = new BinNode(data, this));
	}

	Ptr insertAsRightChild(const T& data) {
		return (rChild_ = new BinNode(data, this));
	}	

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
};

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
