#pragma once

namespace dtl
{

//! 累计T类对象的特征（总和）
template <typename T>
struct CRC
{
	T& c;
	
	CRC(T& cc)
		: c(cc)
	{}

	virtual void operator()(T& e) {
		c += e;
	}
};

//! 判断一个T类容器是否局部有序
template <typename T>
struct CheckOrder
{
	T pred;
	int& unsorted;

	CheckOrder(int& unsorted_, T& first)
		: pred(first)
		, unsorted(unsorted_)
	{}

	virtual void operator()(T& e) {
		if (pred > e) {
			unsorted++;
		}
		pred = e;
	}
};


}
