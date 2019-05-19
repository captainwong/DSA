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

//! ����
template <typename T>
class List
{
	typedef ListNode<T> Node;
	typedef Node* NodePtr;

private:
	//! ��ģ
	int size_ = 0;
	//! ͷ���ڱ�
	NodePtr header = nullptr;
	//! β���ڱ�
	NodePtr trailer = nullptr;

public:
	// Constructor
	List() { init(); }
	//! ���帴��L
	List(List<T> const& L) { copy_nodes(L.first(), L.size_); }
	//! �����б�L����λ��p���n��
	List(List<T> const& L, Rank r, int n) { copy_nodes(L[r], n); }
	//! �����б�����λ��p���n��
	List(NodePtr p, int n) { copy_nodes(p, n); }

#if ENABLE_INITIALIZER_LIST
	//! ��std::initialize_list ����
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
	//! �׽ڵ㣨����Ϊ�գ�
	NodePtr first() const { return header->succ; }
	//! ĩ�ڵ㣨����Ϊ�գ�
	NodePtr last() const { return trailer->pred; }
	//! �Ƿ�Ϸ��ڵ㣨����ȫ�����ж��Ƿ�Ϊ���Ҳ���ͷ�ڱ���β�ڱ���
	bool valid(NodePtr p) const { return p && p != header && p != trailer; }

	//! ѭ�ȷ��� O(n)
	T& operator[] (Rank r) const {
		assert(0 <= r && r < size_);
		auto p = first();
		while (r--) { p = p->succ; }
		return p->data;
	}

	//! ������������� O(n)
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

	//! �����б���� O(n)
	NodePtr find(T const& e) const { return find(e, size_, trailer); }
	//! ����������� O(n)
	NodePtr find(T const& e, int n, NodePtr p) const {
		while (n--) { 
			if ((p = p->pred)->data == e) { 
				return p;
			}
		}
		return nullptr;
	}

	//! �����б���� O(n)
	NodePtr search(T const& e) const { return search(e, size_, trailer); }
	//! ����������� O(n)
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

	//! ��������� O(n)
	NodePtr select_max() { return selectMax(header->succ, size_); }
	//! ��p����n-1�������ѡ������� O(n)
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

	/****4������ O(1) **********/

	NodePtr insert_as_first(T const& e) { size_++; return header->insert_as_succ(e); }
	NodePtr insert_as_last(T const& e) { size_++; return trailer->insert_as_pred(e); }
	NodePtr insert_after(NodePtr p, T const& e) { size_++; return p->insert_as_succ(e); }
	NodePtr insert_before(NodePtr p, T const& e) { size_++;return p->insert_as_pred(e); }

	//! ɾ���ڵ㣬�������� O(1)
	T remove(NodePtr p) {
		assert(valid(p)); 
		T data = p->data;
		p->pred->succ = p->succ; 
		p->succ->pred = p->pred;
		delete p; size_--; 
		return data;
	}

	//! ȫ�б�鲢 O(N), N = size_ + L.size_
	void merge(List<T>& L) { merge(first(), size_, L, L.first(), L.size_); }
	//! ��������
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
	//! ��������
	void sort() { sort(first(), size_); }

	//! ����ȥ�� O(n^2)
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

	//! ����ȥ�� O(n)
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

	//! ǰ����
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
	* @brief �����б�Ĺ鲢
	* @param p ���б��ڽڵ�p�����ã��鲢���ʱָʾ����������
	* @param n ���б��ڴ�p��ʼ�ڵ�����
	* @param L Ҫ�鲢���б�
	* @param q L�Ľڵ�q
	* @param m L�ڴӽڵ�q��ʼ�ڵ�����
	* @note �ڹ鲢����ʱ���п���this == L && rank(p) + n == rank(q)
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

	//! �鲢���� O(nlogn)
	void merge_sort(NodePtr& p, int n) {
		if (n < 2) return;
		int m = n >> 1; NodePtr q = p;
		for (int i = 0; i < m; i++) { q = q->succ; }
		merge_sort(p, m);
		merge_sort(q, n - m);
		merge(p, m, *this, q, n - m);
	}

	//! ѡ������ O(n^2)
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
	* @brief ��������
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
