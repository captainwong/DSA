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
	bool hasParent() const { return parent_; }
	bool hasLChild() const { return lChild_; }
	bool hasRChild() const { return rChild_; }
	bool hasChild() const { return lChild_ || rChild_; }
	bool hasBothChild() const { return lChild_ && rChild_; }
	bool isLeaf() const { return !hasChild(); }
	Ptr sibling() const { return isLChild() ? parent_->rChild_ : parent_->lChild_; }
	Ptr uncle() const { return parent_->isLChild() ? parent_->parent_->rChild_ : parent_->parent_->lChild_; }

	Ptr insertAsLeftChild(const T& data) {
		return (lChild_ = new BinNode(data, this));
	}

	Ptr insertAsRightChild(const T& data) {
		return (rChild_ = new BinNode(data, this));
	}	

	//! ��λ�ڵ�v��ֱ�Ӻ��
	Ptr succ() {
		auto s = this; // ��¼��̵���ʱ����
		if (rChild_) { // �����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
			s = rChild_; // ��������
			while (s->lChild_) {  s = s->lChild_; } // �����С���Ľڵ�
		} else { // ����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
			while (s->isRChild()) { s = s->parent_; } // ������������֧�����ϳ����Ϸ��ƶ�
			s = s->parent_; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
		}
		return s;
	}
};

//! �ڵ�߶�
template <typename T>
int stature(BinNode<T>* node)
{
	return node ? node->height_ : -1;
}

//! ����ƽ��
template <typename T>
bool balanced(BinNode<T>* node)
{
	return stature(node->lChild_) == stature(node->rChild_);
}

//! ƽ������
template <typename T>
int balanceFactor(BinNode<T>* node)
{
	return stature(node->lChild_) - stature(node->rChild_);
}

//! AVL ƽ��
template <typename T>
bool avlBalanced(BinNode<T>* node)
{
	auto factor = balanceFactor(node);
	return (-2 < factor) && (factor < 2);
}
