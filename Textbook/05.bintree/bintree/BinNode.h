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

//! �����Һ�����ȡ������
// ��AVLƽ�����ǰ�����ȷ���ع�����
template <typename T>
BinNode<T>* tallerChild(BinNode<T>* node)
{
	return 
	stature(node->lChild_) > stature(node->rChild_) ? node->lChild_ : ( // ���
		stature(node->lChild_) < stature(node->rChild_) ? node->rChild_ : ( // �Ҹ�
			node->isLChild() ? node->lChild_ : node->rChild_)); // �ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������
}
