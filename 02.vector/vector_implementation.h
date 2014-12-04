#include <assert.h>
#include <stdlib.h>
#include "fibnacci.h"

namespace JTL // Jack's template library
{
	template <typename T>
	void Vector<T>::copy_from(T const* A, Rank lo, Rank hi)
	{
		_elem = new T[_capacity = 2 * (hi - lo)];
		_size = 0;
		while (lo < hi) {
			_elem[_size++] = A[lo++];
		}
	}


	template <typename T>
	void Vector<T>::expand()
	{
		if (_size < _capacity) {
			return;
		}

		if (_capacity < DEFAULT_CAPACITY) {
			_capacity = DEFAULT_CAPACITY;
		}

		T* old_elem = _elem;
		_elem = new T[_capacity <<= 1];
		for (int i = 0; i < _size; i++) {
			_elem[i] = old_elem[i];
		}

		delete[] old_elem;
	}

	template <typename T>
	int Vector<T>::disordered() const
	{
		int n = 0;
		for (int i = 1; i < _size; i++) {
			if (_elem[i - 1] > _elem[i]) {
				n++;
			}
		}
		return n;
	}

	template <typename T>
	Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
	{
		assert(0 <= lo);
		assert(lo < hi);
		assert(hi <= _size);

		while ((lo < hi--) && (e != _elem[hi])) {}
		return hi;
	}

	template <typename T>
	Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
	{
		assert(0 <= lo);
		assert(lo < hi);
		assert(hi <= _size);

		//return (rand() % 2) ?
		//	binary_search(_elem, e, lo, hi) : fibnacci_search(_elem, e, lo, hi);
		return fibnacci_search(_elem, e, lo, hi);
	}

	template <typename T>
	Rank Vector<T>::binary_search(T* A, T const& e, Rank lo, Rank hi)
	{
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
		// 查找失败时，简单地返回-1，而不能只是失败的位置
#endif

		// version 2
#ifdef USE_VERSION_2
		while (1 < hi - lo) {	// 每步迭代仅需一次比较
			Rank mi = (lo + hi) >> 1;
			(e < A[mi]) ? hi = mi : lo = mi;
		}// 出口时hi = lo + 1，查找区间仅含一个元素A[lo]
		return (e == A[lo]) ? lo : -1; // 查找成功时返回对应的秩，否则统一返回-1
		// 有多个命中元素时，不能保证返回秩最大者；
		// 查找失败时，简单地返回-1，而不能只是失败的位置
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


	template <typename T>
	Rank Vector<T>::fibnacci_search(T* A, T const& e, Rank lo, Rank hi)
	{
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
		// 查找失败时，简单地返回-1，而不能只是失败的位置
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


	template <typename T>
	Rank Vector<T>::interpolation_search(T* A, T const& e, Rank lo, Rank hi)
	{
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


	template <typename T>
	void Vector<T>::shrink()
	{
		if (_capacity < DEFAULT_CAPACITY << 1) { return; }
		if (_size << 2 > _capacity) { return; }
		T* old_elem = _elem;
		_elem = new T[_capacity >= 1];
		for (int i = 0; i < _size; i++) {
			_elem[i] = old_elem[i];
		}
		delete[] old_elem;
	}


	template <typename T>
	bool Vector<T>::bubble(Rank lo, Rank hi)
	{
		bool sorted = true;
		while (++lo < hi) {
			if (_elem[lo - 1] > _elem[lo]) {
				sorted = false;
				swap(_elem[lo - 1], _elem[lo]);
			}
		}
		return sorted;
	}


	template <typename T>
	void Vector<T>::bubble_sort(Rank lo, Rank hi)
	{
		assert(0 <= lo);
		assert(lo < hi);
		assert(hi <= _size);

		while (!bubble(lo, hi--)) {}
	}


	template <typename T>
	Rank Vector<T>::bubble_fast(Rank lo, Rank hi)
	{
		Rank last = lo;
		while (++lo < hi) {
			if (_elem[lo - 1] > _elem[lo]) {
				last = lo;
				swap(_elem[lo - 1], _elem[lo]);
			}
		}
		return last;
	}


	template <typename T>
	void Vector<T>::bubble_sort_fast(Rank lo, Rank hi)
	{
		assert(0 <= lo);
		assert(lo < hi);
		assert(hi <= _size);

		while (lo < (hi = bubble_fast(lo, hi))) {}
	}


	template <typename T>
	void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
	{
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


	template <typename T>
	void Vector<T>::merge_sort(Rank lo, Rank hi)
	{
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


	template <typename T>
	T& Vector<T>::operator[] (Rank r) const
	{
		assert(r >= 0 && r < _size);
		return _elem[r];
	}


	template <typename T>
	Vector<T>& Vector<T>::operator= (Vector<T> const& V)
	{
		if (_elem) {
			delete[] _elem;
		}

		copy_from(V._elem, 0, V._size);
		return *this;
	}


	template <typename T>
	int Vector<T>::remove(Rank lo, Rank hi)
	{
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


	template <typename T>
	T Vector<T>::remove(Rank r)
	{
		assert(r >= 0 && r < _size);
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}


	template <typename T>
	Rank Vector<T>::insert(Rank r, T const& e)
	{
		assert(r >= 0 && r <= _size);
		expand();
		for (int i = _size; i > r; i--) {
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;
		return r;
	}


	template <typename T>
	void Vector<T>::sort(Rank lo, Rank hi)
	{
		/*switch (rand() % 2) {
			case 0:	bubble_sort_fast(lo, hi);	break;
			case 1:	merge_sort(lo, hi);			break;
		}*/
		merge_sort(lo, hi);
	}


	template <typename T>
	void Vector<T>::unsort(Rank lo, Rank hi)
	{
		T* V = _elem + lo;
		for (Rank i = hi - lo; i > 0; i--) {
			swap(V[i] - 1, V[rand() % i]);
		}
	}


	template <typename T>
	int Vector<T>::deduplicate()
	{
		int old_size = _size;
		int i = 1;
		while (i < _size) {
			(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
		}
		return old_size - _size;
	}


	template <typename T>
	int Vector<T>::uniquify()
	{
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

};





