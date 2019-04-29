#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include "config.h"
#include "fibnacci.h"
#include "swap.h"
//#include "priority_queue.h" // heap sort

#ifdef TEST_BUILD
#include <stdlib.h> // rand
#endif

namespace dtl 
{

//! 秩
typedef int Rank;

template <typename T>
class Vector
{
protected:
	//! 规模
	Rank size_;
	//! 容量
	int capacity_;
	//! 数据
	T* elem_;

public:
	//! 默认初始容量
	static constexpr int DEFAULT_CAPACITY = 3;

	//! 容量为c、规模为n，所有元素初始为v
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
		assert(s <= c);
		elem_ = new T[capacity_ = c]; 
		size_ = 0; 
		while (size_ < s) { 
			elem_[size_++] = v; 
		}
	}

	//! 从数组整体构造
	Vector(T const* A, Rank n) {
		copy_from(A, 0, n); 
	}

	//! 从数组区间构造
	Vector(T const* A, Rank lo, Rank hi) { 
		copy_from(A, lo, hi); 
	}

	//! 从向量整体复制
	Vector(Vector<T> const& V) { 
		copy_from(V.elem_, 0, V.size_);
	}

	//! 从向量区间复制
	Vector(Vector<T> const& V, Rank lo, Rank hi) { 
		copy_from(V.elem_, lo, hi); 
	}

	//! 从向量整体复制
	Vector<T>& operator=(Vector<T> const& V) { 
		if (elem_) { 
			delete[] elem_;
		}
		copy_from(V.elem_, 0, V.size_);
		return *this;
	}

	~Vector() { 
		delete[] elem_;
	}


	/************** Read only ***************************************/

	Rank size() const { return size_; }
	bool empty() const { return !size_; }

	//! 相邻逆序对的总数
	int disordered() const {
		int n = 0; 
		for (int i = 1; i < size_; i++) { 
			if (elem_[i - 1] > elem_[i]) { 
				n++; 
			}
		}
		return n;
	}

	/**
	* @brief 无序向量的顺序查找
	* @return 查找成功时返回元素e最后一次出现的位置（秩）；失败时返回lo-1
	* @warn input sensitive 输入敏感，平均O(n)
	*/
	Rank find(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo && lo < hi && hi <= size_);
		while ((lo < hi--) && (e != elem_[hi])) {} 
		return hi;
	}

	//! 无序向量整体查找
	Rank find(T const& e) const { return find(e, 0, size_); }

	//! 有序向量查找，返回不大于e的最后一个节点的秩
	Rank search(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo); assert(lo < hi); assert(hi <= size_);
#ifdef TEST_BUILD
		return (rand() % 2) ?
			binary_search(elem_, e, lo, hi) : fibnacci_search(elem_, e, lo, hi);
#else
		return fibnacci_search(elem_, e, lo, hi);
#endif
	}

	Rank search(T const& e) const { 
		return (0 >= size_) ? -1 : search(e, 0, size_); 
	}


	/************* Mutable *****************************/

	//! 下标
	T& operator[] (Rank r) const { 
		assert(0 <= r && r < size_); 
		return elem_[r]; 
	}

	//! 插入元素 
	Rank insert(Rank r, T const& e) { // input sensitive 输入敏感，平均O(n)
		assert(0 <= r && r <= size_);
		expand();
		for (int i = size_; i > r; i--) { // r之后的元素整体右移
			elem_[i] = elem_[i - 1];
		}
		elem_[r] = e;
		size_++;
		return r;
	}

	//! 作为末尾元素插入
	Rank insert(T const& e) { return insert(size_, e); }

	int remove(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
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

	T remove(Rank r) {
		assert(0 <= r && r < size_);
		T e = elem_[r];
		remove(r, r + 1);
		return e;
	}


	//! 对[lo, hi)排序
	void sort(Rank lo, Rank hi) {
#ifdef TEST_BUILD
		bubble_sort(lo, hi);
		//heapSort(lo, hi);
#endif // TEST_BUILD

		merge_sort(lo, hi); 
	}

	//! 整体排序
	void sort() { sort(0, size_); }

	//! 对区间[lo, hi)（等概率随机）置乱
	void unsort(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		T* V = elem_ + lo;
		for (Rank i = hi - lo; i > 0; i--) {
			swap(V[i] - 1, V[rand() % i]);
		}
	}

	//! 整体（等概率随机）置乱
	void unsort() { unsort(0, size_); }

	//! 无序去重 O(n^2)
	int deduplicate() {	// unsorted
		int old_size = size_;
		int i = 1;
		while (i < size_) {
			(find(elem_[i], 0, i) < 0) ? i++ : remove(i);
		}
		return old_size - size_;
	}

	//! 有序去重 O(n)
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


	/****************** Traverse *******************************/

	void traverse(void(*visit)(T&)) {
		for (int i = 0; i < size_; i++) { visit(elem_[i]); }
	}

	template <typename VST>
	void traverse(VST& visit) {
		for (int i = 0; i < size_; i++) { visit(elem_[i]); }
	}

protected:
	//! 辅助构造，以数组区间A[lo, hi)为蓝本复制向量
	void copy_from(T const* A, Rank lo, Rank hi) {
		elem_ = new T[capacity_ = 2 * (hi - lo)]; size_ = 0; 
		while (lo < hi) { elem_[size_++] = A[lo++]; }
	}

	/**
	* @brief 扩容
	* @note 容量满时倍增。分摊意义O(1)时间
	* @note 始终有 size_ <= capacity_ <= 2*size_
	*/
	void expand() {
		if (size_ < capacity_) { return; }
		if (capacity_ < DEFAULT_CAPACITY) { capacity_ = DEFAULT_CAPACITY; }
		T* old_elem = elem_; 
		elem_ = new T[capacity_ <<= 1];
		for (int i = 0; i < size_; i++) { elem_[i] = old_elem[i]; }
		delete[] old_elem;
	}

	/**
	* @brief 缩容
	* @note 以25%为界，容量减半。相当于expand的逆过程，分摊复杂度O(1)
	* @warn 不适用对单次操作的执行速度敏感的应用场合
	*/
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

	//! 扫描交换
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

	/**
	* @brief 二分查找算法（版本A）
	* @note 在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
	* @warn 有多个命中元素时，不能保证返回秩最大者；
	* @warn 查找失败时，简单地返回-1，而不能指示失败的位置
	* @note 复杂度 平均查找长度为O(1.5 * logn)
	*/
	static Rank binary_search_A(T* A, T const& e, Rank lo, Rank hi) {
		while (lo < hi) {	// 每步迭代可能要做两次比较判断，有三个分支
			Rank mi = (lo + hi) >> 1;
			if (e < A[mi]) {
				hi = mi;
			} else if (A[mi] < e) {
				lo = mi + 1;
			} else {
				return mi;
			}
		}
		return -1;
	}

	/**
	* @brief 二分查找算法（版本B）
	* @note 在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
	* @warn 有多个命中元素时，不能保证返回秩最大者；
	* @warn 查找失败时，简单地返回-1，而不能指示失败的位置
	* @note 渐进复杂度O(logn)，但相比版本A，整体性能更加稳定
	*/
	static Rank binary_search_B(T* A, T const& e, Rank lo, Rank hi) {
		while (1 < hi - lo) {	// 每步迭代仅需一次比较，有两个分支；成功查找不能提前终止
			Rank mi = (lo + hi) >> 1;
			(e < A[mi]) ? hi = mi : lo = mi;
		}// 出口时hi = lo + 1，查找区间仅含一个元素A[lo]
		return (e == A[lo]) ? lo : -1;
	}

	static Rank binary_search(T* A, T const& e, Rank lo, Rank hi) {

#ifdef TEST_BUILD
		binary_search_A(A, e, lo, hi);
		binary_search_B(A, e, lo, hi);
#endif

#define USE_VERSION_3


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

	/**
	* @brief Fibonacci查找算法（版本A）
	* @note 在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
	* @warn 有多个命中元素时，不能保证返回秩最大者；
	* @warn 查找失败时，简单地返回-1，而不能指示失败的位置
	* @note 复杂度 平均查找长度为O(1.44 * logn)
	*/
	static Rank fibnacci_search_A(T* A, T const& e, Rank lo, Rank hi) {
		Fibnacci fib(hi - lo); // 用O(log_phi(n = hi - lo)时间创建Fib数列
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
	}

	static Rank fibnacci_search(T* A, T const& e, Rank lo, Rank hi) {
#ifdef TEST_BUILD
		fibnacci_search_A(A, e, lo, hi);

#endif

#define USE_VERSION_2

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

