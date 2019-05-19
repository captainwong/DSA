#pragma once

#include "config.h"
#include <assert.h>
#include "list_node.h"
#include "swap.h"

#if ENABLE_INITIALIZER_LIST
#include <initializer_list>
#endif

#if TEST_BUILD
#include <stdlib.h> // rand
#endif

namespace dtl 
{

//! 链表
template <typename T>
class List
{
	typedef ListNode<T> Node;
	typedef Node* NodePtr;

private:
	//! 规模
	int size_ = 0;
	//! 头部哨兵
	NodePtr header = nullptr;
	//! 尾部哨兵
	NodePtr trailer = nullptr;

public:
	// Constructor
	List() { init(); }
	//! 整体复制L
	List(List<T> const& L) { copy_nodes(L.first(), L.size_); }
	//! 复制列表L中自位置p起的n项
	List(List<T> const& L, Rank r, int n) { copy_nodes(L[r], n); }
	//! 复制列表中自位置p起的n项
	List(NodePtr p, int n) { copy_nodes(p, n); }

#if ENABLE_INITIALIZER_LIST
	//! 从std::initialize_list 构造
	List(std::initializer_list<T> L) {
		init();
		for (const auto& e : L) {
			insert_as_last(e);
		}
	}
#endif
	
	List<T>& operator=(List<T> const& L) {
		copy_nodes(L.first(), L.size_);
		return *this;
	}

	// Destructor
	~List() { clear(); }


	/********************** Read only ****************************************************/

	Rank size() const { return size_; }
	bool empty() const { return size_ <= 0; }
	//! 首节点（可能为空）
	NodePtr first() const { return header->succ; }
	//! 末节点（可能为空）
	NodePtr last() const { return trailer->pred; }
	//! 是否合法节点（不安全，仅判断是否为空且不是头哨兵、尾哨兵）
	bool valid(NodePtr p) const { return p && p != header && p != trailer; }

	//! 循秩访问 O(n)
	T& operator[] (Rank r) const {
		assert(0 <= r && r < size_);
		auto p = first();
		while (r--) { p = p->succ; }
		return p->data;
	}

	//! 相邻逆序对数量 O(n)
	int disordered() const {
		if (0 == size_) { return 0; } 
		int sum = 0; NodePtr p = first();
		for (int i = 0; i < size_ - 1; p = p->succ, i++) { 
			if (p->data > p->succ->data) { 
				sum++;
			}
		}
		return sum;
	}

	//! 无序列表查找 O(n)
	NodePtr find(T const& e) const { return find(e, size_, trailer); }
	//! 无序区间查找 O(n)
	NodePtr find(T const& e, int n, NodePtr p) const {
		while (n--) { 
			if ((p = p->pred)->data == e) { 
				return p;
			}
		}
		return nullptr;
	}

	//! 有序列表查找 O(n)
	NodePtr search(T const& e) const { return search(e, size_, trailer); }
	//! 有序区间查找 O(n)
	NodePtr search(T const& e, int n, NodePtr p) const {
		assert(0 <= n && n <= size_);
		if (size_ == 0) { return nullptr; } 
		while (n-- && p != header->succ) { 
			if ((p = p->pred)->data <= e) { 
				break;
			}
		}
		return p;
	}

	//! 整体最大者 O(n)
	NodePtr select_max() { return selectMax(header->succ, size_); }
	//! 在p及其n-1个后继中选出最大者 O(n)
	NodePtr select_max(NodePtr p, int n) {
		NodePtr max_p = p;
		for (NodePtr cur = p; 1 < n; n--) { 
			if ((cur = cur->succ)->data >= max_p->data) { 
				max_p = cur;
			}
		}
		return max_p;
	}


	/***************************** Mutable **********************************************/

	//! destruct
	int clear() {
		int old_size = size_;
		while (0 < size_) {
			remove(header->succ);
		}
		return old_size;
	}

	/****4个插入 O(1) **********/

	NodePtr insert_as_first(T const& e) { size_++; return header->insert_as_succ(e); }
	NodePtr insert_as_last(T const& e) { size_++; return trailer->insert_as_pred(e); }
	NodePtr insert_after(NodePtr p, T const& e) { size_++; return p->insert_as_succ(e); }
	NodePtr insert_before(NodePtr p, T const& e) { size_++;return p->insert_as_pred(e); }

	//! 删除节点，返回数据 O(1)
	T remove(NodePtr p) {
		assert(valid(p)); 
		T data = p->data;
		p->pred->succ = p->succ; 
		p->succ->pred = p->pred;
		delete p; size_--; 
		return data;
	}

	//! 全列表归并 O(N), N = size_ + L.size_
	void merge(List<T>& L) { merge(first(), size_, L, L.first(), L.size_); }
	//! 区间排序
	void sort(NodePtr p, int n) {
#if TEST_BUILD
		switch (rand() % 3) {
			case 0: insertion_sort(p, n); break;
			case 1: selection_sort(p, n); break;
			default: merge_sort(p, n); break;
		}
#else
		merge_sort(p, n);
#endif
	}
	//! 整体排序
	void sort() { sort(first(), size_); }

	//! 无序去重 O(n^2)
	int deduplicate() {
		if (size_ < 2) return 0;
		int old_size = size_; 
		NodePtr p = header; 
		Rank r = 0;
		while ((p = p->succ) != trailer) { 
			auto q = find(p->data, r, p);
			q ? remove(q) : r++;
		}
		return old_size - size_;
	}

	//! 有序去重 O(n)
	int uniquify() {
		if (size_ < 2) return 0;
		int old_size = size_; 
		NodePtr p = first();
		NodePtr q;
		while ((q = p->succ) != trailer) {
			if (q->data != p->data) { p = q; }
			else { remove(q); }
		}
		return old_size - size_;
	}

	//! 前后倒置
	void reverse() {
		auto p = header;
		auto q = trailer;
		for (int i = 1; i < size_; i += 2) {
			swap((p = p->succ)->data, (q = q->pred)->data);
		}
	}


	/************************** traverse ****************************************/

	void traverse(void(*visit)(T&)) {
		for (auto p = header->succ; p != trailer; p = p->succ) { visit(p->data); }
	}

	template <typename VST>
	void traverse(VST& visit) {
		for (auto p = header->succ; p != trailer; p = p->succ) { visit(p->data); }
	}


protected:
	//! construct
	void init() {
		if (!header) {
			header = new Node();
		}
		if (!trailer) {
			trailer = new Node();
		}
		header->pred = nullptr; header->succ = trailer;
		trailer->pred = header; trailer->succ = nullptr;
		size_ = 0;
	}

	//! O(n)
	void copy_nodes(NodePtr p, int n) {
		init();
		while (n--) {
			insert_as_last(p->data);
			p = p->succ;
		}
	}

	/**
	* @brief 有序列表的归并
	* @param p 本列表内节点p的引用，归并完成时指示区间的新起点
	* @param n 本列表内从p开始节点数量
	* @param L 要归并的列表
	* @param q L的节点q
	* @param m L内从节点q开始节点数量
	* @note 在归并排序时，有可能this == L && rank(p) + n == rank(q)
	* @note O(n+m)
	*/
	void merge(NodePtr& p, int n, List<T>& L, NodePtr q, int m) {
		NodePtr pp = p->pred; 
		while (0 < m) {
			if ((0 < n) && p->data <= q->data) {
				if (q == (p = p->succ)) { break; }
				n--;
			} else {
				insert_before(p, L.remove((q = q->succ)->pred));
				m--;
			}
		}
		p = pp->succ;
	}

	//! 归并排序 O(nlogn)
	void merge_sort(NodePtr& p, int n) {
		if (n < 2) return;
		int m = n >> 1; NodePtr q = p;
		for (int i = 0; i < m; i++) { q = q->succ; }
		merge_sort(p, m);
		merge_sort(q, n - m);
		merge(p, m, *this, q, n - m);
	}

	//! 选择排序 O(n^2)
	void selection_sort(NodePtr p, int n) {
		NodePtr head = p->pred; NodePtr tail = p;
		for (int i = 0; i < n; i++) { tail = tail->succ; }
		while (1 < n) {
			NodePtr max_p = select_max(head->succ, n);
			insert_before(tail, remove(max_p));
			tail = tail->pred; n--;
		}
	}

	/**
	* @brief 插入排序
	* @note O(n^2)
	*/
	void insertion_sort(NodePtr p, int n) {
		for (int sorted = 0; sorted < n; sorted++) {
			insert_after(search(p->data, sorted, p), p->data);
			p = p->succ; 
			remove(p->pred);
		}
	}

};

}
