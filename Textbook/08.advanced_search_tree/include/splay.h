#pragma once

#include "../../07.bst/bst/bst.h"

//! �ڽڵ�*p��*lc������Ϊ�գ�֮�佨���������ӹ�ϵ
template <typename NodePtr> inline
void attachAsLChild(NodePtr p, NodePtr lc) { p->lChild = lc; if (lc) { lc->parent = p; } }

//! �ڽڵ�*p��*rc������Ϊ�գ�֮�佨�������ң��ӹ�ϵ
template <typename NodePtr> inline
void attachAsRChild(NodePtr p, NodePtr rc) { p->rChild = rc; if (rc) { rc->parent = p; } }


//! ��չ��
template <typename T>
class Splay : public BST<T>
{
public:
	typedef typename BinNode<T> Node;
	typedef typename Node::Ptr NodePtr;

protected:

	//! ��v��չ����
	NodePtr splay(NodePtr v) {
		if (!v) { return nullptr; }
		NodePtr p, g;
		while ((p = v->parent_) && (g = p->parent_)) {
			auto gg = g->parent_; // ÿ��֮��v������ԭ���游Ϊ��
			if (v->isLChild()) {
				if (p->isLChild()) { // zig-zig
					attachAsLChild(g, p->rChild_);
					attachAsLChild(p, v->rChild_);
					attachAsRChild(p, g);
					attachAsRChild(v, p);
				} else { // zig-zag
					attachAsRChild(g, v->lChild_);
					attachAsLChild(p, v->rChild_);
					attachAsLChild(v, g);
					attachAsRChild(v, p);
				}
			} else {
				if (p->isRChild()) { // zag-zag
					attachAsRChild(g, p->lChild_);
					attachAsRChild(p, v->lChild_);
					attachAsLChild(p, g);
					attachAsLChild(v, p);
				} else { // zag-zig
					attachAsRChild(p, v->lChild_);
					attachAsRChild(g, v->rChild_);
					attachAsLChild(v, p);
					attachAsRChild(v, g);
				}
			}

			// �������游gg����v���ھ�������������gg�˺�Ӧ��vΪ����Һ���
			if (!gg) { 
				v->parent_ = nullptr;
			} else {
				(g == gg->lChild_) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
			}

			updateHeight(g);
			updateHeight(p);
			updateHeight(v);

		} // ˫����չ����ʱ������ g==nullptr, ��p���ܷǿ�

		// ��p�����Ǹ���ֻ���ٶ��ⵥ��������һ�Σ�
		if (p = v->parent_) {
			if (v == p->lChild_) {
				attachAsLChild(p, v->rChild_);
				attachAsRChild(v, p);
			} else {
				attachAsRChild(p, v->lChild_);
				attachAsLChild(v, p);
			}

			updateHeight(p);
			updateHeight(v);
		}

		// ��չ��ɣ���������
		v->parent_ = nullptr;
		return v;
	}

public:
	//! ����
	virtual NodePtr& search(const T& e) override {
		// ���ñ�׼BST���ڲ��ӿڶ�λĿ��ڵ�
		auto p = searchIn(this->root_, e, this->hot_ = nullptr);

		// ���۳ɹ������󱻷��ʵĽڵ㶼����չ����
		this->root_ = splay(p ? p : this->hot_);

		//���Ƿ��ظ��ڵ�
		return this->root_;
	}

	//! ����
	virtual NodePtr insert(const T& e) override;

	//! ɾ��
	bool remove(const T& e) override;
};
