#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdlib.h> // rand
#include "fibnacci.h"
#include "swap.h"

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
		_elem = new T[_capacity = c]; 
		_size = 0; 
		while (_size < s) { 
			_elem[_size++] = v; 
		}
	}

	Vector(T const* A, Rank n) {
		copy_from(A, 0, n); 
	}

	Vector(T const* A, Rank lo, Rank hi) { 
		copy_from(A, lo, hi); 
	}

	Vector(Vector<T> const& V) { 
		copy_from(V._elem, 0, V._size);
	}

	Vector(Vector<T> const& V, Rank lo, Rank hi) { 
		copy_from(V._elem, lo, hi); 
	}

	Vector<T>& operator=(Vector<T> const& V) { 
		if (_elem) { 
			delete[] _elem;
		}
		copy_from(V._elem, 0, V._size);
		return *this;
	}

	// Destructor
	~Vector() { 
		delete[] _elem;
	}

	// Read only 
	Rank size() const { return _size; }
	bool empty() const { return !_size; }
	int disordered() const {
		int n = 0; 
		for (int i = 1; i < _size; i++) { 
			if (_elem[i - 1] > _elem[i]) { 
				n++; 
			}
		}
		return n;
	}
	Rank find(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo); assert(lo < hi); assert(hi <= _size);
		while ((lo < hi--) && (e != _elem[hi])) {} 
		return hi;
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
	T remove(Rank r) {
		assert(r >= 0 && r < _size);
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}

	int remove(Rank lo, Rank hi) {
		assert(lo >= 0 && lo <= hi && hi <= _size);
		if (lo == hi) {
			return 0;
		}

		while (hi < _size) {
			_elem[lo++] = _elem[hi++];
		}
		_size = lo;
		shrink();
		return hi - lo;
	}

	Rank insert(Rank r, T const& e) {
		assert(r >= 0 && r <= _size);
		expand();
		for (int i = _size; i > r; i--) {
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;
		return r;
	}

	Rank insert(T const& e) { 
		return insert(_size, e); 
	}

	void sort(Rank lo, Rank hi) {
		merge_sort(lo, hi);
	}

	void sort() { 
		sort(0, _size);
	}

	void unsort(Rank lo, Rank hi) {
		T* V = _elem + lo;
		for (Rank i = hi - lo; i > 0; i--) {
			swap(V[i] - 1, V[rand() % i]);
		}
	}

	void unsort() { unsort(0, _size); }
	int deduplicate() {	// unsorted
		int old_size = _size;
		int i = 1;
		while (i < _size) {
			(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
		}
		return old_size - _size;
	}

	int uniquify() { // sorted
		Rank i = 0, j = 0;
		while (++j < _size) {
			if (_elem[i] != _elem[j]) {
				_elem[++i] = _elem[j];
			}
		}
		_size = ++i;
		shrink();
		return j - i;
	}


	// Traverse
	void traverse(void(*visit)(T&)) {
		for (int i = 0; i < _size; i++) { visit(_elem[i]); }
	}

	template <typename VST>
	void traverse(VST& visit) {
		for (int i = 0; i < _size; i++) { visit(_elem[i]); }
	}

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

	void shrink() {
		if (_capacity < DEFAULT_CAPACITY << 1) { return; }
		if (_size << 2 > _capacity) { return; }
		T* old_elem = _elem;
		_elem = new T[_capacity >>= 1];
		for (int i = 0; i < _size; i++) {
			_elem[i] = old_elem[i];
		}
		delete[] old_elem;
	}

	bool bubble(Rank lo, Rank hi) {
		bool sorted = true;
		while (++lo < hi) {
			if (_elem[lo - 1] > _elem[lo]) {
				sorted = false;
				swap(_elem[lo - 1], _elem[lo]);
			}
		}
		return sorted;
	}

	void bubble_sort(Rank lo, Rank hi) {
		assert(0 <= lo);
		assert(lo < hi);
		assert(hi <= _size);
		while (!bubble(lo, hi--)) {}
	}

	Rank bubble_fast(Rank lo, Rank hi) {
		Rank last = lo;
		while (++lo < hi) {
			if (_elem[lo - 1] > _elem[lo]) {
				last = lo;
				swap(_elem[lo - 1], _elem[lo]);
			}
		}
		return last;
	}

	void bubble_sort_fast(Rank lo, Rank hi) {
		assert(0 <= lo);
		assert(lo < hi);
		assert(hi <= _size);

		while (lo < (hi = bubble_fast(lo, hi))) {}
	}

	void merge(Rank lo, Rank mi, Rank hi) {
		T* A = _elem + lo;
		int lb = mi - lo;
		T* B = new T[lb];	// [lo, mi)
		for (int i = 0; i < lb; i++) {
			B[i] = A[i];
		}
		T* C = _elem + mi;	// [mi, hi)
		int lc = hi - mi;

		for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
			if ((j < lb) && (!(k < lc) || B[j] <= C[k])) {
				A[i++] = B[j++];
			}
			if ((k < lc) && (!(j < lb) || C[k] < B[j])) {
				A[i++] = C[k++];
			}
		}
		delete[] B;
	}

	void merge_sort(Rank lo, Rank hi) {
		assert(0 <= lo);
		assert(lo < hi);
		assert(hi <= _size);

		if (hi - lo < 2)
			return;

		Rank mi = (hi + lo) >> 1;
		merge_sort(lo, mi);
		merge_sort(mi, hi);
		merge(lo, mi, hi);
	}

	// Common functions
	static Rank binary_search(T* A, T const& e, Rank lo, Rank hi) {
		assert(0 <= lo);
		assert(lo <= hi);
		//assert(hi <= _size);

#define USE_VERSION_3

	// version 1
#ifdef USE_VERSION_1
		while (lo < hi) {	// 每步迭代可能要做两次比较判断，有三个分支
			Rank mi = (lo + hi) >> 1;
			if (e < A[mi]) {
				hi = mi;
			} else if (A[i] < e) {
				lo = mi + 1;
			} else {
				return mi;
			}
		}
		return -1;
		// 有多个命中元素时，不能保证返回秩最大者；
		// 查找失败时，简单地返回-1，而不能指示失败的位置
#endif

	// version 2
#ifdef USE_VERSION_2
		while (1 < hi - lo) {	// 每步迭代仅需一次比较
			Rank mi = (lo + hi) >> 1;
			(e < A[mi]) ? hi = mi : lo = mi;
		}// 出口时hi = lo + 1，查找区间仅含一个元素A[lo]
		return (e == A[lo]) ? lo : -1; // 查找成功时返回对应的秩，否则统一返回-1
		// 有多个命中元素时，不能保证返回秩最大者；
		// 查找失败时，简单地返回-1，而不能指示失败的位置
#endif

	// version 3
#ifdef USE_VERSION_3
		while (lo < hi) {	// 每步迭代仅需一次比较
			Rank mi = (lo + hi) >> 1;
			(e < A[mi]) ? hi = mi : lo = mi + 1;
		}// 成功查找不能提前终止
		return --lo;//循环结束时，lo为大于e的元素的最小秩，故lo-1即不大于e的元素的最大秩
		// 有多个命中元素时，总能保证返回秩最大者
		// 查找失败时，能够返回失败的位置
#endif
	}

	static Rank fibnacci_search(T* A, T const& e, Rank lo, Rank hi) {
		assert(0 <= lo);
		assert(lo <= hi);
		//assert(hi <= A->_size);

#define USE_VERSION_2

#ifdef USE_VERSION_1
		Fibnacci fib(hi - lo);
		while (lo < hi) {
			while (hi - lo < fib.get()) {
				fib.prev();
			}
			Rank mi = lo + fib.get() - 1;
			if (e < A[mi]) {
				hi = mi;
			} else if (A[mi] < e) {
				lo = mi + 1;
			} else {
				return mi;
			}
		}
		return -1;
		// 有多个元素命中时，不能保证返回秩最大者
		// 查找失败时，简单地返回-1，而不能指示失败的位置
#endif

#ifdef USE_VERSION_2
		Fibnacci fib(hi - lo);
		while (lo < hi) {
			while (hi - lo < fib.get()) { fib.prev(); }
			Rank mi = lo + fib.get() - 1;
			(e < A[mi]) ? hi = mi : lo = mi + 1;
		}// 成功查找不能提前终止
		return --lo;//循环结束时，lo为大于e的元素的最小秩，故lo-1即不大于e的元素的最大秩
		// 有多个命中元素时，总能保证返回秩最大者
		// 查找失败时，能够返回失败的位置
#endif
	}

	static Rank interpolation_search(T* A, T const& e, Rank lo, Rank hi) {
		assert(0 <= lo);
		assert(lo <= hi);
		assert(hi <= A->_size);

		while (A[lo] <= e && e <= A[hi]) {
			Rank mi = lo + (hi - lo) * (e - A[lo]) / (A[hi] - A[lo]);
			if (A[mi] < e) {
				lo = mi + 1;
			} else if (e < A[mi]) {
				hi = mi - 1;
			} else {
				return mi;
			}
		}

		if (A[lo] == e) {
			return lo;
		} else {
			return -1;
		}
	}
};

}

