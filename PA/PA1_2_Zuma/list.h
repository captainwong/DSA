#pragma once

#include <assert.h>
#include "list_node.h"

template <typename T>
class List
{
private:
	int size_;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	void init();
	int clear();
	void copy_nodes(ListNodePosi(T), int);
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
	void merge_sort(ListNodePosi(T)&, int);
	void selection_sort(ListNodePosi(T), int);
	void insertion_sort(ListNodePosi(T), int);

public:
	// Constructor
	List() { init(); }
	List(List<T> const& L);
	List(List<T> const& L, Rank r, int n);
	List(ListNodePosi(T) p, int n);

	// Destructor
	~List();

	// Read only
	Rank size() const { return size_; }
	bool empty() const { return size_ <= 0; }
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	bool valid(ListNodePosi(T) p) { return p && p != header && p != trailer; }
	T& operator[] (Rank r) const;
	int disordered() const;
	ListNodePosi(T) find(T const& e) const { return find(e, size_, trailer); }
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search(T const& e) const { return search(e, size_, trailer); }
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) select_max() { return selectMax(header->succ, size_); }
	ListNodePosi(T) select_max(ListNodePosi(T) p, int n);

	// Writable
	ListNodePosi(T) insert_as_first(T const& e);
	ListNodePosi(T) insert_as_last(T const& e);
	ListNodePosi(T) insert_after(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insert_before(ListNodePosi(T) p, T const& e);
	T remove(ListNodePosi(T) p);
	void merge(List<T>& L) { merge(first(), size_, L, L.first(), L.size_); }
	void sort(ListNodePosi(T) p, int n);
	void sort() { sort(first(), size_); }
	int deduplicate();	// unsorted
	int uniquify();		// sorted
};

#include "list_implementation.h"

