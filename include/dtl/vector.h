#pragma once

#include <assert.h>

namespace dtl 
{

typedef int Rank;

template <typename T>
class Vector
{
protected:
	Rank	_size;
	int		_capacity;
	T*		_elem;

	static constexpr int DEFAULT_CAPACITY = 3;

public:
	// Constructors
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
		_elem = new T[_capacity = c]; _size = 0; while (_size < s) { _elem[_size++] = v; }
	}
	Vector(T const* A, Rank n) { copy_from(A, 0, n); }
	Vector(T const* A, Rank lo, Rank hi) { copy_from(A, lo, hi); }
	Vector(Vector<T> const& V) { copy_from(V._elem, 0, V._size); }
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copy_from(V._elem, lo, hi); }
	Vector<T>& operator=(Vector<T> const& V) { if (_elem) { delete[] _elem; } copy_from(V._elem, 0, V._size); return *this; }

	// Destructor
	~Vector() { delete[] _elem; }

	// Read only 
	Rank size() const { return _size; }
	bool empty() const { return !_size; }
	int disordered() const {
		int n = 0; for (int i = 1; i < _size; i++) { if (_elem[i - 1] > _elem[i]) { n++; } } return n;
	}
	Rank find(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo); assert(lo < hi); assert(hi <= _size);
		while ((lo < hi--) && (e != _elem[hi])) {} return hi;
	}
	Rank find(T const& e) const { return find(e, 0, _size); }
	Rank search(T const& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); }
	Rank search(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo); assert(lo < hi); assert(hi <= _size);
		//return (rand() % 2) ?
		//	binary_search(_elem, e, lo, hi) : fibnacci_search(_elem, e, lo, hi);
		return fibnacci_search(_elem, e, lo, hi);
	}
	T& operator[] (Rank r) const { assert(r >= 0 && r < _size); return _elem[r]; }

	// Mutable
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);
	Rank insert(T const& e) { return insert(_size, e); }
	void sort(Rank lo, Rank hi);
	void sort() { sort(0, _size); }
	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size); }
	int deduplicate();	// unsorted
	int uniquify();		// sorted

protected:
	void copy_from(T const* A, Rank lo, Rank hi) {
		_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0; 
		while (lo < hi) { _elem[_size++] = A[lo++]; }
	}
	void expand() {
		if (_size < _capacity) { return; }
		if (_capacity < DEFAULT_CAPACITY) { _capacity = DEFAULT_CAPACITY; }
		T* old_elem = _elem; _elem = new T[_capacity <<= 1];
		for (int i = 0; i < _size; i++) { _elem[i] = old_elem[i]; }
		delete[] old_elem;
	}
	void shrink();
	bool bubble(Rank lo, Rank hi);
	void bubble_sort(Rank lo, Rank hi);
	Rank bubble_fast(Rank lo, Rank hi);
	void bubble_sort_fast(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);
	void merge_sort(Rank lo, Rank hi);

	// Common functions
	static Rank binary_search(T* A, T const& e, Rank lo, Rank hi);
	static Rank fibnacci_search(T* A, T const& e, Rank lo, Rank hi);
	static Rank interpolation_search(T* A, T const& e, Rank lo, Rank hi);
};

}

#include "vector_implementation.h"
