#pragma once

#include "btnode.h"

/*
* @brief B-树
* @note N个节点，m阶
* @note 高度 h = θ(log(m, N)); 
* @note 每个节点的分支数，最低为 (m/2)的上整， 最高为m个
* @note 每个节点的关键码数为分支数-1，即最低为 (m/2)的上整-1， 最高为m-1个
*/
template <typename T>
class BTree
{
public:
	typedef BTNode<T> Node;
	typedef Node* NodePtr;

protected:
	//! 关键码总数
	int N_;
	//! B-树的阶次，至少为3————创建时指定，一般不能修改
	int m_;
	//! 根节点
	NodePtr root_;
	//! search() 最后访问的非空（除非树空）的节点位置
	NodePtr hot_;

protected:
	//! 因插入而上溢之后的分裂处理
	void solveOverflow(NodePtr node) {
		if (node->child_.size() < m_) { return; } // 递归基：当前节点并未上溢
		auto s = m_ / 2; // 轴点（此时应有m = key.size() = child.size() - 1）
						 // 发生上溢的节点，应恰好有m个关键码，m+1个分支
						 // 将m个孩子以中位数s，分为左侧[0, s)，轴点s, 以及右侧[s+1, m)
						 // 因此分别有s个，1个，m-s-1个关键码
		auto u = new Node(); // 注意：新节点已有一个空孩子
		for (Rank i = 0; i < m_ - s - 1; i++) { // node 右侧的m-s-1个孩子及关键码分裂为右侧节点u
			u->child_.insert(i, node->child_.remove(s + 1)); // 逐个移动效率低
			u->key_.insert(i, node->key_.remove(s + 1)); // todo 此策略可以改进
		}
		u->child_[m_ - s - 1] = node->child_.remove(s + 1); //  移动node最靠右的孩子
		if (u->child_[0]) { // 若u的孩子们非空
			for (Rank i = 0; i < m_ - s; i++) { u->child_[i]->parent_ = u; } // 将孩子们的父节点统一指向u
		}
		auto p = node->parent_;
		if (!p) { root_ = p = new Node(); p->child_[0] = node; node->parent_ = p; }
		auto r = 1 + p->key_.search(node->key_[0]); // p中指向node的指针的秩+1，即为u应有的秩
		p->key_.insert(r, node->key_.remove(s)); // 轴点关键码上升
		p->child_.insert(r + 1, u); u->parent_ = p; // 新节点u与父节点p互联
		solveOverflow(p); // 上升一层，如有必要则继续分裂 —— 至多递归h = O(logN)层
	}

	//! 因删除而下溢之后的合并处理
	void solveUnderflow(NodePtr node) {
		if ((m_ + 1) / 2 <= node->child_.size()) { return; } // 递归基：当前节点并未下溢
		auto p = node->parent_;
		if (!p) { // 递归基：已到根节点，没有孩子的下限
			if (node->key_.empty() && node->child_[0]) {
				// 但倘若作为树根的node已不含关键码，却有（唯一的）非空孩子，则
				root_ = node->child_[0]; root_->parent_ = nullptr; // 这个节点可被跳过
				node->child_[0] = nullptr; /* release(node); */ // 并因不再有用而被销毁
			} // 整树高度降低一层
			return;
		}
		// 确定node是p的第r个孩子 —— 此时node可能不含关键码，故不能通过关键码查找
		// 另外，在实现了孩子指针的判等器之后，也可直接调用vector::find定位
		Rank r = 0; while (p->child_[r] != node) { r++; }

		// 情况1：向左兄弟借关键码
		if (0 < r) { // 若node不是p的第一个孩子
			auto ls = p->child_[r - 1]; // 左兄弟必存在
			if ((m_ + 1) / 2 < ls->child_.size()) { // 若该兄弟足够“胖”，则
				node->key_.insert(0, p->key_[r - 1]); // p借出一个关键码给node（作为最小关键码）
				p->key_[r - 1] = ls->key_.remove(ls->key_.size() - 1); // ls的最大关键码转入p
				node->child_.insert(0, ls->child_.remove(ls->child_.size() - 1)); // 同时ls的最右侧孩子过继给node				
				if (node->child_[0]) { node->child_[0]->parent_ = node; } // 作为node的最左侧孩子
				return; // 至此，通过右旋已完成当前层（以及所有层）的下溢处理
			}
		} // 至此，左兄弟要么为空，要么太“瘦”

		// 情况2：向右兄弟借关键码
		if (r < p->child_.size() - 1) { // 若node不是p的最后一个孩子
			auto rs = p->child_[r + 1]; // 右兄弟必存在
			if ((m_ + 1) / 2 < rs->child_.size()) { // 若该兄弟足够“胖”，则
				node->key_.insert(node->key_.size(), p->key_[r]); // p借出一个关键码给v（作为最大关键码
				p->key[r] = rs->key_.remove(0); // rs的最小关键码转入p
				node->child_.insert(node->child_.size(), rs->child_.remove(0)); // 同时rs的最左侧孩子过继给node
				if (node->child_[node->child_.size() - 1]) { // 作为node的最右侧孩子
					node->child_[node->child_.size() - 1]->parent_ = node;
				}
				return; // 至此，通过左旋已完成当前层（以及所有层）的下溢处理
			}
		} // 至此，右兄弟要么为空，要么太“瘦”

		// 情况3：左、右兄弟要么为空（但不可能同时），要么都太“瘦” —— 合并
		if (0 < r) { // 与左兄弟合并
			auto ls = p->child_[r - 1]; // 左兄弟必存在
			ls->key_.insert(ls->key_.size(), p->key_.remove(r - 1)); p->child_.remove(r);
			// p的第r-1个关键码转入ls，node不再是p的第r个孩子
			ls->child_.insert(ls->child_.size(), node->child_.remove(0));
			if (ls->child_[ls->child_.size() - 1]) { // node的最左侧孩子过继给ls做最右侧孩子
				ls->child_[ls->child_.size() - 1]->parent_ = ls;
			}
			while (!node->key_.empty()) { // node剩余的关键码和孩子，依次转入ls
				ls->key_.insert(ls->key_.size(), node->key_.remove(0));
				ls->child_.insert(ls->child_.size(), node->child_.remove(0));
				if (ls->child_[ls->child_.size() - 1]) {
					ls->child_[ls->child_.size() - 1]->parent_ = ls;
				}
			}
			/* release(node); */
		} else { // 与右兄弟合并
			auto rs = p->child_[r + 1]; // 右兄弟必存在
			rs->key_.insert(0, p->key_.remove(r)); p->child_.remove(r);
			// p的第r个关键码转入rs，node不再是p的第r个孩子
			rs->child_.insert(0, node->child_.remove(node->child_.size() - 1));
			if (rs->child_[0]) { rs->child_[0].parent = rs; } // node的最左侧孩子过继给rs做最左侧孩子
			while (!node->key_.empty()) { // node剩余的关键码和孩子，依次转入rs
				rs->key_.insert(0, node->key_.remove(node->key_.size() - 1));
				rs->child_.insert(0, node->child_.remove(node->child_.size() - 1));
				if (rs->child_[0]) { rs->child_[0]->parent_ = rs; }
			}
			/* release(node); */
		}

		solveUnderflow(p); // 上升一层，如有必要继续旋转或合并 —— 至多递归h = O(logN)层
	}

public:
	BTree(int order = 3) : m_(order), N_(0) { root_ = new Node(); }
	~BTree() { if (root_) { /*release(root_);*/ } }

	//! 阶次
	int order() const { return m_; }
	//! 规模
	int size() const { return N_; }
	//! 树根
	NodePtr& root() { return root_; }
	//! 判空
	bool empty() const { return !root_; }

	/*
	* @brief 查找
	* @param e 关键码
	* @return 成功时返回目标关键码所在的节点，上层调用过程可在该节点内进一步查找以确定准确的命中位置；
	*		  失败时返回对应外部节点，其父节点由变量hot_指示
	* @note 复杂度O(log(m, N))
	* @note 尽管时间复杂度没有渐进意义上的改进，但相对而言极其耗时的I/O操作的次数，
	*		已经大致缩减为BST的1/log(2, m)倍，实际的访问效率将有十分可观的提高。
	*/
	NodePtr search(const T& e) {
		auto v = root_; hot_ = nullptr;
		while (v) { // 逐层查找
			auto r = v->key_.search(e);
			if ((0 <= r) && (e == v->key_[r])) { return v; } // 查找成功
			hot_ = v; v = v->child_[r + 1]; // 否则，转入对应子树（hot_指向其父）—— 需做I/O，最费时间
		} // todo 这里在向量内是二分查找，但对通常的order_可直接顺序查找
		return nullptr; // 失败：最终抵达外部节点
	}

	//! 插入
	bool insert(const T& e) {
		auto v = search(e); if (v) { return false; } // e已存在时直接返回
		auto r = hot_->key_.search(e); // 在节点hot_的有序关键码内查找合适的插入位置
		hot_->key_.insert(r + 1, e); // 将新关键码插入对应位置
		hot_->child_.insert(r + 2, nullptr); N_++; // 创建空子树指针		
		solveOverflow(hot_); // 如有必要，需做分裂
		return true;
	}

	//! 删除
	bool remove(const T& e) {
		auto v = search(e); if (!v) { return false; } // 确认目标关键码存在
		auto r = v->key_.search(e); // 确定目标关键码在节点v中的秩
		if (v->child_[0]) { // 若v非叶子，则e的直接后继必属于某叶节点
			auto u = v->child_[r + 1]; // 在右子树中一直向左
			while (u->child_[0]) { u = u->child_[0]; } // 找到e的后继
			v->key_[r] = u->key_[0]; v = u; r = 0; // 并与之交换位置
		} // 至此，v必然位于最底层，且其中第r个关键码就是待删除者
		v->key_.remove(r); v->child_.remove(r + 1); N_--; // 删除e，以及其下两个外部节点之一
		solveUnderflow(v); // 如有必要，需做旋转或合并
		return true;
	}
};
