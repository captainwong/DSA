#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <assert.h>
#include <stdlib.h> // rand
#include "config.h"
#include "fibnacci.h"
#include "swap.h"
//#include "priority_queue.h" // heap sort
#if ENABLE_INITIALIZER_LIST
#include <initializer_list>
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
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = {}) {
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

#if ENABLE_INITIALIZER_LIST
	//! 从std::initialize_list 构造
	Vector(std::initializer_list<T> V) {
		elem_ = new T[capacity_ = V.size()];
		for (const auto& v : V) {
			elem_[size_++] = v;
		}
	}
#endif

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

	//! 无序向量整体查找 O(n)
	Rank find(T const& e) const { return find(e, 0, size_); }

	//! 有序向量区间查找，返回不大于e的最后一个节点的秩 O(logn)
	Rank search(T const& e, Rank lo, Rank hi) const {
		assert(0 <= lo && lo <= hi && hi <= size_);
#if TEST_BUILD
		return (rand() % 2) ?
			binary_search(elem_, e, lo, hi) : fibnacci_search(elem_, e, lo, hi);
#else
		return fibnacci_search(elem_, e, lo, hi);
#endif
	}

	//! 有序向量查找，O(logn)
	Rank search(T const& e) const { 
		return (0 >= size_) ? -1 : search(e, 0, size_); 
	}


	/************* Mutable *****************************/

	//! 下标 O(1)
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

	//! 作为末尾元素插入 O(1)
	Rank insert(T const& e) { return insert(size_, e); }

	//! 删除[lo, hi)内元素 
	int remove(Rank lo, Rank hi) { // input sensitive 输入敏感，平均O(n)
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

	//! 删除元素 O(n)
	T remove(Rank r) {
		assert(0 <= r && r < size_);
		T e = elem_[r];
		remove(r, r + 1);
		return e;
	}

	//! 对[lo, hi)排序
	void sort(Rank lo, Rank hi) {
#if TEST_BUILD		
		switch (rand() % 6) {
			case 0: bubble_sort(lo, hi); break;
			case 1: bubble_sort_fast(lo, hi); break;
			case 2: bubble_sort_fast_2(lo, hi); break;
			case 3: insertion_sort(lo, hi); break;
			case 4: selection_sort(lo, hi); break;
			default: merge_sort(lo, hi);
		}
#else
		merge_sort(lo, hi);
#endif // TEST_BUILD
	}

	//! 整体排序
	void sort() { sort(0, size_); }

	//! 对区间[lo, hi)（等概率随机）置乱
	void unsort(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		T* V = elem_ + lo;
		for (Rank i = hi - lo; i > 0; i--) {
			swap(V[i - 1], V[rand() % i]);
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

	/**
	* @brief 冒泡排序
	* @note O(n^2)
	* @note 稳定算法 stable algorithm
	*/
	void bubble_sort(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		while (!bubble(lo, hi--)) {}
	}

	//! 快速起泡，返回最右侧的逆序对位置，对[lo, hi)左侧部分有序时可以加快速度
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

	//! 冒泡排序加速版1，对[lo, hi)左侧部分有序时可以加快速度
	void bubble_sort_fast(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		while (lo < (hi = bubble_fast(lo, hi))) {}
	}

	//! 快速起泡2，返回最左侧的逆序对位置，对[lo, hi)右侧部分有序时可以加快速度
	Rank bubble_fast_2(Rank lo, Rank hi) {
		Rank first = hi;
		while (lo < --hi) {
			if (elem_[hi] < elem_[hi + 1]) {
				first = hi;
				swap(elem_[hi], elem_[hi + 1]);
			}
		}
		return first;
	}

	//! 冒泡排序加速版2，对[lo, hi)两侧部分有序时可以加快速度，对两侧无序、中间有序无效
	void bubble_sort_fast_2(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		while ((lo = bubble_fast_2(lo, hi) < (hi = bubble_fast(lo, hi)))) {}
	}

	//! 归并各自有序的子向量[lo, mi)和[mi, hi)
	void merge(Rank lo, Rank mi, Rank hi) {
		T* A = elem_ + lo; // 合并后的向量A = elem_[lo, hi)
		int lengthB = mi - lo; 
		T* B = new T[lengthB];	// [lo, mi)
		for (int i = 0; i < lengthB; i++) {
			B[i] = A[i];
		}
		T* C = elem_ + mi;	// [mi, hi)
		int lengthC = hi - mi;

		// B[j]和C[k]中的小者续至A末尾
		for (int i = 0, j = 0, k = 0; (j < lengthB) || (k < lengthC);) {
			if ((j < lengthB) && (!(k < lengthC) || B[j] <= C[k])) {
				A[i++] = B[j++];
			}
			if ((k < lengthC) && (!(j < lengthB) || C[k] < B[j])) {
				A[i++] = C[k++];
			}
		}
		delete[] B;
	}

	/**
	* @brief 归并排序
	* @note 由冯·诺依曼于1945年在EDVAC上首次编程实现
	* @note 是第一个可以在最坏情况下依然保持O(nlogn)运行时间的确定性排序算法
	*/
	void merge_sort(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		if (hi - lo < 2) { // 递归基
			return;
		}
		Rank mi = (hi + lo) >> 1;
		merge_sort(lo, mi);
		merge_sort(mi, hi);
		if (elem_[mi - 1] > elem_[mi]) { // 增加此句，可以改进归并算法在最好情况下的速度
			merge(lo, mi, hi);
		}
	}

	//! 插入排序 O(n^2)
	void insertion_sort(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		for (Rank r = lo + 1; r < hi; r++) {
			Rank i = fibnacci_search_B(elem_, elem_[r], lo, r);
			insert(i + 1, remove(r));
		}
	}

	//! 选取最大元素 [lo, hi]
	Rank getMax(Rank lo, Rank hi) const {
		Rank m = hi;
		while (lo < hi--) {
			if (elem_[m] < elem_[hi]) {
				m = hi;
			}
		}
		return m;
	}

	//! 选择排序 O(n^2)
	void selection_sort(Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= size_);
		while (lo < --hi) {
			swap(elem_[getMax(lo, hi)], elem_[hi]);
		}
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

	/**
	* @brief 二分查找算法（版本C）
	* @note 在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
	* @note 有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置
	* @note 渐进复杂度O(logn)
	*/
	static Rank binary_search_C(T* A, T const& e, Rank lo, Rank hi) {
		while (lo < hi) {	// 每步迭代仅需一次比较
			Rank mi = (lo + hi) >> 1;
			(e < A[mi]) ? hi = mi : lo = mi + 1;
		} // 成功查找不能提前终止
		return --lo;//循环结束时，lo为大于e的元素的最小秩，故lo-1即不大于e的元素的最大秩
	}

	//! 在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
	static Rank binary_search(T* A, T const& e, Rank lo, Rank hi) {
#if TEST_BUILD
		switch (rand() % 3) {
			case 0: return binary_search_A(A, e, lo, hi);
			case 1: return binary_search_B(A, e, lo, hi);
			default: return binary_search_C(A, e, lo, hi);
		}
#else
		return binary_search_C(A, e, lo, hi);
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
		Fibnacci<int> fib(hi - lo); // 用O(log_phi(n = hi - lo)时间创建Fib数列
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

	/**
	* @brief Fibonacci查找算法（版本B）
	* @note 在有序向量的区间[lo, hi)内查找元素e，0 <= lo <= hi <= _size
	* @note 有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置
	* @note 复杂度 平均查找长度为O(1.44 * logn)
	*/
	static Rank fibnacci_search_B(T* A, T const& e, Rank lo, Rank hi) {
		Fibnacci<int> fib(hi - lo); // 用O(log_phi(n = hi - lo)时间创建Fib数列
		while (lo < hi) {
			while (hi - lo < fib.get()) { fib.prev(); }
			Rank mi = lo + fib.get() - 1;
			(e < A[mi]) ? hi = mi : lo = mi + 1;
		}// 成功查找不能提前终止
		return --lo;//循环结束时，lo为大于e的元素的最小秩，故lo-1即不大于e的元素的最大秩
	}

	static Rank fibnacci_search(T* A, T const& e, Rank lo, Rank hi) {
#if TEST_BUILD
		switch (rand() % 2) {
			case 0: return fibnacci_search_A(A, e, lo, hi);
			default: return fibnacci_search_B(A, e, lo, hi);
		}
#else
		return fibnacci_search_B(A, e, lo, hi);
#endif
	}

	static Rank interpolation_search(T* A, T const& e, Rank lo, Rank hi) {
		assert(0 <= lo && lo <= hi && hi <= A->size_);
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

