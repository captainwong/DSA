#pragma once

namespace dtl 
{

//! 二分递归版 O(2^n)
static __int64 fibR(int n)
{
	return n < 2 ? n : fibR(n - 1) + fibR(n - 2);
}

//! 线性递归版 O(n)
static __int64 fibL(int n, __int64& prev)
{
	if (n == 0) {
		prev = 1; return 0; // fib(-1) = 1, fib(0) = 0
	} else {
		__int64 prev_prev; prev = fibL(n - 1, prev_prev);
		return prev_prev + prev;
	}
}

//! 迭代版 O(n)
static __int64 fibI(int n)
{
	__int64 f = 0, g = 1; // fib(0) = 0, fib(1) = 1
	while (n--) {
		g += f; f = g - f;
	}
	return f;
}


//! Fibonacci数列类
template <typename T = int>
class Fibnacci
{
private:
	T f, g;

public:
	//! 初始化为不小于n的最小Fibonacci项，O(log_phi(n))时间
	explicit Fibnacci(T n = 0) {
		f = 1;
		g = 0;
		while (g < n) {
			next();
		}
	}

	//! 获取当前Fibonacci项，O(1)时间
	T get() const { return g; }

	//! 转至下一Fibonacci项，O(1)时间
	T next() {
		g += f;
		f = g - f;
		return g;
	}

	//! 转至上一Fibonacci项，O(1)时间
	T prev() {
		f = g - f;
		g -= f;
		return g;
	}
};

}
