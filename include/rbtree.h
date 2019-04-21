#pragma once

#include "bst.h"

template <typename T>
class RBTree : public BST<T>
{
public:
	typedef BinNode<T> Node;
	typedef Node* NodePtr;

	//! ������д
	virtual NodePtr insert(const T& e) override {
		auto& x = this->search(e); if (x) { return x; }
		x = new Node(e, this->hot_, nullptr, nullptr, -1, RBColor::RB_RED);
		solveDoubleRed(x); return x ? x : this->hot_->parent_;
	}

	//! ɾ����д
	virtual bool remove(const T& e) override {
		auto& x = this->search(e); if (!x) { return false; }
		auto r = this->removeAt(x, this->hot_); if (!(--this->size_)) { return true; }
		// hot_ĳһ���Ӹձ�ɾ�����ұ�r��ָ�ڵ㣨������nullptr�����档���¼���Ƿ�ʧ�⣬������Ҫ����
		if (!this->hot_) { // ���ձ�ɾ�����Ǹ��ڵ㣬�����úڣ������ºڸ߶�
			this->root_->color_ = RBColor::RB_BLACK; this->updateHeight(this->root_); return true;
		}
		// ���£�ԭx����r���طǸ���_hot�طǿ�
		if (blackHeightUpdated(this->hot_)) { return true; } // ���������ȵĺ������Ȼƽ�⣬���������
		if (isRed(r)) { r->color_ = RBColor::RB_RED; r->height_++; return true; } // ������rΪ�죬��ֻ������ת��
		// ���£�ԭx����r����Ϊ��ɫ
		solveDoubleBlack(r); return true;
	}

protected:
	/*
	* @brief ˫������
	* @note RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
	*	RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
	*	RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
	*/
	void solveDoubleRed(NodePtr x) { // x��ǰ��Ϊ��
		// ���ѣ��ݹ飩ת������������ת�ڣ������ڸ߶�Ҳ��֮����
		if (x->isRoot()) { this->root_->color_ = RBColor::RB_BLACK; this->root_->height_++; return; }
		// ����x�ĸ���p�ش���
		auto p = x->parent_; if (isBlack(p)) { return; } // ��pΪ�ڣ������ֹ����������
		auto g = p->parent_; // ��ȻpΪ�죬��x���游�ش��ڣ��ұ�Ϊ��ɫ
		auto u = x->uncle(); // ���£���x�常u����ɫ�ֱ���		
		if (isBlack(u)) { // RR-1: uΪ��ɫ����nullptr��ʱ
			if (x->isLChild() == p->isLChild()) { // ��x��pͬ�ࣨ��zIg-zIg��zAg-zAg������
				p->color_ = RBColor::RB_BLACK; // p�ɺ�ת�ڣ�x���ֺ�
			} else { // ��x��p��ࣨ��zIg-zAg��zAg-zIg������
				x->color_ = RBColor::RB_BLACK; // x�ɺ�ת�ڣ�p���ֺ�
			}
			g->color_ = RBColor::RB_RED; // g�ض��ɺ�ת��
			// todo �����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ
			// ����ת�󽫸��úڡ������ú죬��������Ⱦɫ��Ч�ʸ���
			auto gg = g->parent_;
			auto r = this->fromParentTo(g) = this->rotateAt(x); // ��������������ڵ�
			r->parent_ = gg; // ��ԭ���游����
		} else { // RR-2: uΪ��ɫ
			p->color_ = RBColor::RB_BLACK; p->height_++; // p�ɺ�ת��
			u->color_ = RBColor::RB_BLACK; u->height_++; // u�ɺ�ת��
			if (!g->isRoot()) { g->color_ = RBColor::RB_RED; } // g���Ǹ�����ת��
			solveDoubleRed(g); // todo ��������g��������β�ݹ飬���Ż�Ϊ������ʽ��
		}
	}

	/*
	* @brief ˫������
	* @note RedBlack˫�ڵ����㷨������ڵ�x�뱻������Ľڵ��Ϊ��ɫ������
	*   ��Ϊ�����๲���������
	*	BB-1 ��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
	*	BB-2R��2����ɫ��ת��2�κڸ߶ȸ��£�0����ת�����ٵݹ�
	*	BB-2B��1����ɫ��ת��1�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
	*	BB-3 ��2����ɫ��ת��2�κڸ߶ȸ��£�1����ת��תΪBB-1��BB2R
	*/
	void solveDoubleBlack(NodePtr r) {
		auto p = r ? r->parent_ : this->hot_; if (!p) { return; }
		auto s = r->sibling();
		if (isBlack(s)) { // �ֵ�sΪ��ɫ
			// s�ĺ캢�ӣ������Һ��ӽԺ죬�������ȣ��Ժ�ʱΪNULL��
			auto t = isRed(s->lChild_) ? s->lChild_ : (isRed(s->rChild_) ? s->rChild_ : nullptr);
			if (t) { // BB-1: ��s�к캢��
				auto oldColor = p->color_; // ����ԭ�������ڵ�p��ɫ������t���丸�ס��游
				// ���£�ͨ����ת��ƽ�⣬���������������Һ���Ⱦ��
				auto b = this->fromParentTo(p) = this->rotateAt(t); // ��ת
				if (b->lChild_) { b->lChild_->color_ = RBColor::RB_BLACK; this->updateHeight(b->lChild_); }
				if (b->rChild_) { b->rChild_->color_ = RBColor::RB_BLACK; this->updateHeight(b->rChild_); }
				b->color_ = oldColor; this->updateHeight(b); // ���������ڵ�̳�ԭ���ڵ����ɫ
			} else { // ��s�޺캢��
				s->color_ = RBColor::RB_RED; s->height_--; // sת��
				if (isRed(p)) { // BB-2R
					p->color_ = RBColor::RB_BLACK; // pת�ڣ����ڸ߶Ȳ���
				} else { // BB-2B
					p->height_--; // p���ֺڣ����ڸ߶��½�
					solveDoubleBlack(p); // �ݹ�����
				}
			}
		} else { // BB-3: �ֵ�sΪ��
			s->color_ = RBColor::RB_BLACK; p->color_ = RBColor::RB_RED; // sת�ڣ�pת��
			auto t = s->isLChild() ? s->lChild_ : s->rChild_; // ȡt���丸sͬ��
			this->hot_ = p; this->fromParentTo(p) = this->rotateAt(t); // ��t���丸�ס��游��ƽ�����
			solveDoubleBlack(r); // ��������r��˫�� ���� ��ʱ��p��ת�죬�ʺ���ֻ����BB-1��BB-2R
		}
	}

	//! ���½ڵ�߶���д
	virtual int updateHeight(NodePtr node) override {
		// ����һ��ڸ߶���ȣ����ǳ���˫��
		// ������и��ڵ����Һ��ӵĺڸ߶�ͨ�����
		// ����֮����ȡ����ֵ���Ǳ�����ɾ���ڵ���ƽ����������У���ȷ���±�ɾ���ڵ㸸�׵ĺڸ߶�
		// ����rotateAt()����ݱ�ɾ���ڵ������ߣ��߶�Сһ�����ø��ڵ�ĺڸ߶�
		node->height_ = stature(node->lChild_) < stature(node->rChild_) ? stature(node->rChild_) : stature(node->lChild_);
		return isBlack(node) ? node->height_++ : node->height_; // ����ǰ�ڵ�Ϊ�ڣ����������
		// ��ͳһ����stature(nullptr) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�
	}
};