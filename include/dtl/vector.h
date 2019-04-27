#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdlib.h> // rand
#include "fibnacci.h"
#include "swap.h"
//#include "priority_queue.h" // heap sort

namespace dtl 
{

typedef int Rank;

template <typename T>
class Vector
{
protected:
	Rank	size_;
	int		capacity_;
	T*		elem_;

	static constexpr int DEFAULT_CAPACITY = 3;

public:
	// Constructors
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
		elem_ = new T[capacity_ = c]; 
		size_ = 0; 
		while (size_ < s) { 
			elem_[size_++] = v; 
		}
	}

	Vector(T const* A, Rank n) {
		copy_from(A, 0, n); 
	}

	Vector(T const* A, Rank lo, Rank hi) { 
		copy_from(A, lo, hi); 
	}

	Vector(Vector<T> const& V) { 
		copy_from(V.elem_, 0, V.size_);
	}

	Vector(Vector<T> const& V, Rank lo, Rank hi) { 
		copy_from(V.elem_, lo, hi); 
	}

	Vector<T>& operator=(Vector<T> const& V) { 
		if (elem_) { 
			delete[] elem_;
		}
		copy_from(V.elem_, 0, V.size_);
		return *this;
	}

	// Destructor
	~Vector() { 
		delete[] elem_;
	}

	// Read only 
	Rank size() const { return size_; }
	bool empty() const { return !size_; }
	int disordered() const {
		int n = 0; 
		for (int i = 1; i < size_; i++) { 
			if (elem_[i - 1] > elem_[i]) { 
				n++; 
			}
		}
		return n;
	}
	Rank find(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo); assert(lo < hi); assert(hi <= size_);
		while ((lo < hi--) && (e != elem_[hi])) {} 
		return hi;
	}
	Rank find(T const& e) const { return find(e, 0, size_); }
	Rank search(T const& e) const { return (0 >= size_) ? -1 : search(e, 0, size_); }
	Rank search(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo); assert(lo < hi); assert(hi <= size_);
		//return (rand() % 2) ?
		//	binary_search(elem_, e, lo, hi) : fibnacci_search(elem_, e, lo, hi);
		return fibnacci_search(elem_, e, lo, hi);
	}
	T& operator[] (Rank r) const { assert(r >= 0 && r < size_); return elem_[r]; }

	// Mutable
	T remove(Rank r) {
		assert(r >= 0 && r < size_);
		T e = elem_[r];
		remove(r, r + 1);
		return e;
	}

	int remove(Rank lo, Rank hi) {
		assert(lo >= 0 && lo <= hi && hi <= size_);
		if (lo == hi) {
			return 0;
		}

		while (hi < size_) {
			elem_[lo++] = elem_[hi++];
		}
		size_ = lo;
		shrink();
		return hi - lo;
	}

	//! 插入元素
	Rank insert(Rank r, T const& e) {
		assert(r >= 0 && r <= size_);
		expand();
		for (int i = size_; i > r; i--) {
			elem_[i] = elem_[i - 1];
		}
		elem_[r] = e;
		size_++;
		return r;
	}

	//! 默认作为末元素插入
	Rank insert(T const& e) { return insert(size_, e); }

	//! 对[lo, hi)排序
	void sort(Rank lo, Rank hi) {
#define TEST_BUILD
#ifdef TEST_BUILD
		bubble_sort(lo, hi);
		//heapSort(lo, hi);
#endif // TEST_BUILD

		merge_sort(lo, hi); 
	}

	//! 整体排序
	void sort() { sort(0, size_); }

	//! 对[lo, hi)置乱
	void unsort(Rank lo, Rank hi) {
		T* V = elem_ + lo;
		for (Rank i = hi - lo; i > 0; i--) {
			swap(V[i] - 1, V[rand() % i]);
		}
	}

	//! 整体置乱
	void unsort() { unsort(0, size_); }

	//! 无序去重
	int deduplicate() {	// unsorted
		int old_size = size_;
		int i = 1;
		while (i < size_) {
			(find(elem_[i], 0, i) < 0) ? i++ : remove(i);
		}
		return old_size - size_;
	}

	//! 有序去重
	int uniquify() { // sorted
		Rank i = 0, j = 0;
		while (++j < size_) {
			if (elem_[i] != elem_[j]) {
				elem_[++i] = elem_[j];
			}
		}
		size_ = ++i;
		shrink();
		return j - i;
	}


	// Traverse
	void traverse(void(*visit)(T&)) {
		for (int i = 0; i < size_; i++) { visit(elem_[i]); }
	}

	template <typename VST>
	void traverse(VST& visit) {
		for (int i = 0; i < size_; i++) { visit(elem_[i]); }
	}

protected:
	void copy_from(T const* A, Rank lo, Rank hi) {
		elem_ = new T[capacity_ = 2 * (hi - lo)]; size_ = 0; 
		while (lo < hi) { elem_[size_++] = A[lo++]; }
	}

	void expand() {
		if (size_ < capacity_) { return; }
		if (capacity_ < DEFAULT_CAPACITY) { capacity_ = DEFAULT_CAPACITY; }
		T* old_elem = elem_; 
		elem_ = new T[capacity_ <<= 1];
		for (int i = 0; i < size_; i++) { elem_[i] = old_elem[i]; }
		delete[] old_elem;
	}

	void shrink() {
		if (capacity_ < DEFAULT_CAPACITY << 1) { return; }
		if (size_ << 2 > capacity_) { return; }
		T* old_elem = elem_;
		elem_ = new T[capacity_ >>= 1];
		for (int i = 0; i < size_; i++) {
			elem_[i] = old_elem[i];
		}
		delete[] old_elem;
	}

	bool bubble(Rank lo, Rank hi) {
		bool sorted = true;
		while (++lo < hi) {
			if (elem_[lo - 1] > elem_[lo]) {
				sorted = false;
				swap(elem_[lo - 1], elem_[lo]);
			}
		}
		return sorted;
	}

	void bubble_sort(Rank lo, Rank hi) {
		assert(0 <= lo); assert(lo < hi); assert(hi <= size_);
		while (!bubble(lo, hi--)) {}
	}

	Rank bubble_fast(Rank lo, Rank hi) {
		Rank last = lo;
		while (++lo < hi) {
			if (elem_[lo - 1] > elem_[lo]) {
				last = lo;
				swap(elem_[lo - 1], elem_[lo]);
			}
		}
		return last;
	}

	void bubble_sort_fast(Rank lo, Rank hi) {
		assert(0 <= lo); assert(lo < hi); assert(hi <= size_);
		while (lo < (hi = bubble_fast(lo, hi))) {}
	}

	void merge(Rank lo, Rank mi, Rank hi) {
		T* A = elem_ + lo;
		int lb = mi - lo;
		T* B = new T[lb];	// [lo, mi)
		for (int i = 0; i < lb; i++) {
			B[i] = A[i];
		}
		T* C = elem_ + mi;	// [mi, hi)
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
		assert(0 <= lo); assert(lo < hi); assert(hi <= size_);

		if (hi - lo < 2)
			return;

		Rank mi = (hi + lo) >> 1;
		merge_sort(lo, mi);
		merge_sort(mi, hi);
		merge(lo, mi, hi);
	}

	/*void heapSort(Rank lo, Rank hi) {
		CompleteHeap<T> heap(elem_ + lo, hi - lo);
		while (!heap.empty()) {
			elem_[--hi] = heap.delMax();
		}
	}*/

	// Common functions
	static Rank binary_search(T* A, T const& e, Rank lo, Rank hi) {
		assert(0 <= lo); assert(lo <= hi); //assert(hi <= size_);

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
		//assert(hi <= A->size_);

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
		assert(0 <= lo); assert(lo <= hi); assert(hi <= A->size_);

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

