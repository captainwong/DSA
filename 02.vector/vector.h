#pragma once

namespace JTL // Jack's template library
{
	/*
	size()			报告向量当前的规模
	get(r)			获取秩为r的元素
	put(r, e)		用e替换秩为r的元素
	insert(r, e)	e作为秩为r元素插入，原后继元素依次后移
	remove(r)		删除秩为r的元素，返回该元素中原存放的对象
	disordered()	判断所有元素是否已按非降序排列
	sort()			调整各元素的位置，使之按非降序排列
	find(e)			查找目标元素e
	search(e)		查找目标元素e，返回不大于e且秩最大的元素		（有序向量）
	deduplicate		剔除重复元素
	uniquify()		剔除重复元素									（有序向量）
	traverse()		遍历向量并统一处理所有元素，处理方法由函数对象指定
	*/


	typedef int Rank;
	static const int DEFAULT_CAPACITY = 3;

	//template <typename T>
	//void swap(T& a, T& b)
	//{
	//	T t = a;
	//	a = b;
	//	b = t;
	//}

	template <typename T>
	class Vector
	{
	protected:
		Rank	_size;
		int		_capacity;
		T*		_elem;

	public:
		// Constructors
		Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
		{
			_elem = new T[_capacity = c];
			for (_size = 0; _size < s; _elem[_size++] = v) {}
		}

		Vector(T const* A, Rank n)
		{
			copy_from(A, 0, n);
		}

		Vector(T const* A, Rank lo, Rank hi)
		{
			copy_from(A, lo, hi);
		}

		Vector(Vector<T> const& V)
		{
			copy_from(V._elem, 0, V._size);
		}

		Vector(Vector<T> const& V, Rank lo, Rank hi)
		{
			copy_from(V._elem, lo, hi);
		}

		// Destructor
		~Vector()
		{
			delete[] _elem;
		}

		// Read only 
		Rank size() const { return _size; }
		bool empty() const { return !_size; }
		int disordered() const;
		Rank find(T const& e, Rank lo, Rank hi) const;
		Rank find(T const& e) const { return find(e, 0, _size); }
		Rank search(T const& e) const { return (0 >= _size) ? -1 : search(e, 0, _size); }
		Rank search(T const& e, Rank lo, Rank hi) const;
		T& operator[] (Rank r) const;
		Vector<T>& operator = (Vector<T> const& V);
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
		void copy_from(T const* A, Rank lo, Rank hi);
		void expand();
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
};

#include "vector_implementation.h"
