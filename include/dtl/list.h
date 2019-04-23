#pragma once

#include <assert.h>
#include "list_node.h"

namespace dtl 
{

template <typename T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef Node* NodePtr;

private:
	int _size;
	NodePtr header;
	NodePtr trailer;

protected:
	void init() {
		header = new ListNode<T>; trailer = new ListNode<T>;
		header->pred = nullptr; header->succ = trailer;
		trailer->pred = header; trailer->succ = nullptr; _size = 0;
	}
	int clear() { int old_size = _size; while (0 < _size) { remove(header->succ); } return old_size; }
	void copy_nodes(NodePtr p, int n) { init(); while (n--) { insert_as_last(p->data); p = p->succ; } }
	void merge(NodePtr& p, int n, List<T>& L, NodePtr q, int m) {
		NodePtr pp = p->pred; while (0 < m) {
			if ((0 < n) && p->data <= q->data) { if (q == (p = p->succ)) { break; } n--;
			} else { insert_before(p, L.remove((q = q->succ)->pred)); m--; }
		} p = pp->succ;
	}
	void merge_sort(NodePtr& p, int n) {
		if (n < 2) return; int m = n >> 1; NodePtr q = p;
		for (int i = 0; i < m; i++) { q = q->succ; }
		merge_sort(p, m); merge_sort(q, n - m); merge(p, m, *this, q, n - m);
	}
	void selection_sort(NodePtr p, int n) {
		NodePtr head = p->pred; NodePtr tail = p;
		for (int i = 0; i < n; i++) { tail = tail->succ; }
		while (1 < n) {  NodePtr max_p = select_max(head->succ, n);
			insert_before(tail, remove(max_p)); tail = tail->pred; n--; }
	}
	void insertion_sort(NodePtr p, int n) {
		for (int sorted = 0; sorted < n; sorted++) { 
			insert_after(search(p->data, sorted, p), p->data);  p = p->succ; remove(p->pred);
		}
	}

public:
	// Constructor
	List() { init(); }
	List(List<T> const& L) { copy_nodes(L.first(), L._size); }
	List(List<T> const& L, Rank r, int n) { copy_nodes(L[r], n); }
	List(NodePtr p, int n) { copy_nodes(p, n); }

	// Destructor
	~List() { clear(); delete header; delete trailer; }

	// Read only
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	NodePtr first() const { return header->succ; }
	NodePtr last() const { return trailer->pred; }
	bool valid(NodePtr p) const { return p && p != header && p != trailer; }
	T& operator[] (Rank r) const {
		assert(0 <= r && r < _size);
		auto p = first();
		while (r--) { p = p->succ; }
		return p->data;
	}
	int disordered() const {
		if (0 == _size) { return 0; } int sum = 0; NodePtr p = first();
		for (int i = 0; i < _size - 1; p = p->succ, i++) { if (p->data > p->succ->data) { sum++; } }
		return sum;
	}
	NodePtr find(T const& e) const { return find(e, _size, trailer); }
	NodePtr find(T const& e, int n, NodePtr p) const {
		assert(valid(p)); while (n--) { if ((p = p->pred)->data == e) { return p; } } return nullptr;
	}
	NodePtr search(T const& e) const { return search(e, _size, trailer); }
	NodePtr search(T const& e, int n, NodePtr p) const {
		if (_size == 0) { return nullptr; } assert(0 <= n && n <= _size);
		while (n-- && p != header->succ) { if ((p = p->pred)->data <= e) { break; } } return p;
	}
	NodePtr select_max() { return selectMax(header->succ, _size); }
	NodePtr select_max(NodePtr p, int n) {
		NodePtr max_p = p;
		for (NodePtr cur = p; 1 < n; n--) { if ((cur = cur->succ)->data >= max_p->data) { max_p = cur; } }
		return max_p;
	}

	// Mutable
	NodePtr insert_as_first(T const& e) { _size++; return header->insert_as_succ(e); }
	NodePtr insert_as_last(T const& e) { _size++; return trailer->insert_as_pred(e); }
	NodePtr insert_after(NodePtr p, T const& e) { _size++; return p->insert_as_succ(e); }
	NodePtr insert_before(NodePtr p, T const& e) { _size++;return p->insert_as_pred(e); }
	T remove(NodePtr p) {
		assert(valid(p)); T data = p->data;
		p->pred->succ = p->succ; p->succ->pred = p->pred;
		delete p; _size--; return data;
	}
	void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); }
	void sort(NodePtr p, int n) { merge_sort(p, n); }
	void sort() { sort(first(), _size); }
	//! unsorted
	int deduplicate() {
		if (_size < 2) return 0;
		int old_size = _size; NodePtr p = header; Rank r = 0;
		while ((p = p->succ) != trailer) { find(p->data, r, p) ? remove(p) : r++; }
		return old_size - _size;
	}
	// sorted
	int uniquify() {
		if (_size < 2) return 0;
		int old_size = _size; NodePtr p = first(); NodePtr q;
		while ((q = p->succ) != trailer) { if (q->data != p->data) { p = q; } else { remove(q); } }
		return old_size - _size;
	}

	void traverse(void(*visit)(T&)) {
		for (auto p = header->succ; p != trailer; p = p->succ) { visit(p->data); }
	}

	template <typename VST>
	void traverse(VST& visit) {
		for (auto p = header->succ; p != trailer; p = p->succ) { visit(p->data); }
	}
};

}
