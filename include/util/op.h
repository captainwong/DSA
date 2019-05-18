#pragma once

namespace dtl
{

//! 自增
template <typename T>
struct Increase
{
	virtual void operator()(T& e) {
		e++;
	}
};

//! 倍增
template <typename T>
struct Double
{
	virtual void operator()(T& e) {
		e *= 2;
	}
};

//! 按照Hailstone规则转化一个T类对象
template <typename T>
struct Hailstone
{
	virtual void operator()(T& e) {
		int step = 0;
		while (1 != e) {
			(e % 2) ? (e = 3 * e + 1) : (e /= 2);
			step++;
		}
		e = step;
	}
};

}
