#pragma once

#include <assert.h>
#include "list_node.h"

namespace JTL // Jack's template library
{
	template <typename T>
	class List
	{
	private:
		int _size;
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
		Rank size() const { return _size; }
		bool empty() const { return _size <= 0; }
		ListNodePosi(T) first() const { return header->succ; }
		ListNodePosi(T) last() const { return trailer->pred; }
		bool valid(ListNodePosi(T) p) const { return p && p != header && p != trailer; }
		T& operator[] (Rank r) const;
		int disordered() const;
		ListNodePosi(T) find(T const& e) const { return find(e, _size, trailer); }
		ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
		ListNodePosi(T) search(T const& e) const { return search(e, _size, trailer); }
		ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
		ListNodePosi(T) select_max() { return selectMax(header->succ, _size); }
		ListNodePosi(T) select_max(ListNodePosi(T) p, int n);

		// Writable
		ListNodePosi(T) insert_as_first(T const& e);
		ListNodePosi(T) insert_as_last(T const& e);
		ListNodePosi(T) insert_after(ListNodePosi(T) p, T const& e);
		ListNodePosi(T) insert_before(ListNodePosi(T) p, T const& e);
		T remove(ListNodePosi(T) p);
		void merge(List<T>& L) { merge(first(), _size, L, L.first(), L._size); }
		void sort(ListNodePosi(T) p, int n);
		void sort() { sort(first(), _size); }
		int deduplicate();	// unsorted
		int uniquify();		// sorted
	};
};

#include "list_implementation.h"

