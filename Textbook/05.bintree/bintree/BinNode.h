#pragma once

template <typename T>
struct BinNode
{
	using Ptr = typename BinNode<T>*;

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

	BinNode(const T& data, Ptr parent = nullptr)
		: data_(data)
		, parent_(parent)
		, lChild_(nullptr)
		, rChild_(nullptr)
		, height_(0)
	{
	}

	int size() const {
		int s = 1;
		if (lChild_) { s += lChild_->size(); }
		if (rChild_) { s += rChild_->size(); }
		return s;
	}
	
	bool isRoot() const { return !parent_; }
	bool isLChild() const { return !isRoot() && parent_->lChild_ == this; }
	bool isRChild() const { return !isRoot() && parent_->rChild_ == this; }
	bool hasLChild() const { return lChild_; }
	bool hasRChild() const { return rChild_; }

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

template <typename T>
int stature(BinNode<T>* node)
{
	return node ? node->height_ : -1;
}