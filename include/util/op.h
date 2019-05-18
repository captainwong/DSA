#pragma once

namespace dtl
{

//! ����
template <typename T>
struct Increase
{
	virtual void operator()(T& e) {
		e++;
	}
};

//! ����
template <typename T>
struct Double
{
	virtual void operator()(T& e) {
		e *= 2;
	}
};

//! ����Hailstone����ת��һ��T�����
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
