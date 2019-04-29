#pragma once

namespace dtl 
{

//! ���ֵݹ�� O(2^n)
static __int64 fibR(int n)
{
	return n < 2 ? n : fibR(n - 1) + fibR(n - 2);
}

//! ���Եݹ�� O(n)
static __int64 fibL(int n, __int64& prev)
{
	if (n == 0) {
		prev = 1; return 0; // fib(-1) = 1, fib(0) = 0
	} else {
		__int64 prev_prev; prev = fibL(n - 1, prev_prev);
		return prev_prev + prev;
	}
}

//! ������ O(n)
static __int64 fibI(int n)
{
	__int64 f = 0, g = 1; // fib(0) = 0, fib(1) = 1
	while (n--) {
		g += f; f = g - f;
	}
	return f;
}


//! Fibonacci������
template <typename T = int>
class Fibnacci
{
private:
	T f, g;

public:
	//! ��ʼ��Ϊ��С��n����СFibonacci�O(log_phi(n))ʱ��
	explicit Fibnacci(T n = 0) {
		f = 1;
		g = 0;
		while (g < n) {
			next();
		}
	}

	//! ��ȡ��ǰFibonacci�O(1)ʱ��
	T get() const { return g; }

	//! ת����һFibonacci�O(1)ʱ��
	T next() {
		g += f;
		f = g - f;
		return g;
	}

	//! ת����һFibonacci�O(1)ʱ��
	T prev() {
		f = g - f;
		g -= f;
		return g;
	}
};

}
