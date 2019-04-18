#pragma once

#include "bst.h"

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

		// ��x�ĸ��׳���������ϣ�һ�μ���������g
		for (auto g = x->parent_; g; g = g->parent_) {
			if (!avlBalanced(g)) { // һ������gʧ�⣬��ͨ�������ָ�ƽ��
				this->fromParentTo(g) = this->rotateAt(tallerChild(tallerChild(g)));
				break; // g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ�������
			} else { // ��������Ȼƽ������ȴ�����ֻ��򵥵�
				this->updateHeight(g); // ������߶ȣ�ƽ�����䲻�䣬�߶�ȴ���ܸı䣩
			}
		}

		return xx; // �����½ڵ㣺����ֻ��һ�ε���
	}

	virtual bool remove(T const& e) override {
		auto& x = this->search(e); if (!x) { return false; }
		this->removeAt(x, this->hot_); this->size_--; // �ڰ���BST����ɾ��֮��hot_�������Ⱦ��п���ʧ��

		// ��hot_����ɾ���ڵ�ĸ��ף����������μ���������g
		for (auto g = this->hot_; g; g = g->parent_) {
			if (!avlBalanced(g)) {
				g = this->fromParentTo(g) = this->rotateAt(tallerChild(tallerChild(g)));
			}
			this->updateHeight(g);
		} // ������������(log n)�ε����������Ƿ�����������ȫ���߶Ⱦ������½�

		return true;
	}
};
