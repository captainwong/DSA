#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "deque.h"
#include "dequeex.h"

#define DEFAULT_CAPACITY (64 * 1024)

template <typename T>
T max(T const& a, T const& b)
{
	return a > b ? a : b;
}

//template <typename T>
//class SimpleStack
//{
//private:
//	int _size;
//	int _capacity;
//	T* _elem;
//
//protected:
//	void expand()
//	{
//		if (_size < _capacity)
//			return;
//		T* old_elem = _elem;
//		_capacity <<= 2;
//		_elem = new T[_capacity];
//		for (int i = 0; i < _size; i++) {
//			_elem[i] = old_elem[i];
//		}
//		delete[] old_elem;
//	}
//
//	void shrink()
//	{
//		if (_size > _capacity >> 2 || _capacity >> 2 < DEFAULT_CAPACITY)
//			return;
//
//		T* old_elem = _elem;
//		_capacity >>= 2;
//		_elem = new T[_capacity];
//		for (int i = 0; i < _size; i++) {
//			_elem[i] = old_elem[i];
//		}
//		delete[] old_elem;
//	}
//
//public:
//	SimpleStack(int size = DEFAULT_CAPACITY)
//	{
//		if (size < DEFAULT_CAPACITY)
//			size = DEFAULT_CAPACITY;
//		_size = 0;
//		_capacity = size << 2;
//		_elem = new T[_capacity];
//	}
//
//	~SimpleStack() { delete[] _elem; }
//
//	bool empty() { return _size == 0; }
//
//	void push(T const& e) { expand(); _elem[_size++] = e; }
//
//	T pop() { return _elem[--_size]; }
//
//	T top() { return _size == 0 ? 0 : _elem[_size - 1]; }
//};

#define MAX_INPUT (2000001)

template <typename T>
class Tunel
{
public:
	Tunel() : /*SM(), SS(), SB()*/Q(MAX_INPUT), QQ(MAX_INPUT) {}
	~Tunel() {}

	void enqueue(T const& e)
	{	/**
		 * honor code:
		 * 《习题解析》[10-20]
		 */
		//SM.push(e);
		//SB.push(max(e, SB.top()));
		Q.insert_as_rear(e);
		//if (!QQ.empty())
		//	QQ.enqueue(max(QQ.front(), e));
		int a = 1;
		while (!QQ.empty() && (QQ.rear().key <= e)) {
			a += QQ.remove_rear().counter;
		}
		QQ.insert_as_rear(E(e, a));
	}

	T dequeue()
	{
		/*if (SS.empty()) {
			while (!SM.empty()) {
				SS.push(SM.pop());
				SB.push(max(SB.top(), SS.top()));
			}
		} 

		T e = SS.pop();
		SB.pop();
		return e;*/
		
		/**
		* honor code:
		* 《习题解析》[10-20]
		*/
		if (!(--QQ.front().counter))
			QQ.remove_front();
		return Q.remove_front();
	}

	T getMax()
	{
		/*if (SS.empty()) {
			while (!SM.empty()) {
				SS.push(SM.pop());
				SB.push(max(SB.top(), SS.top()));
			}
		}

		return SB.top();*/

		/**
		* honor code:
		* 《习题解析》[10-20]
		*/
		return QQ.front().key;
	}
private:
	//SimpleStack<T> SM;	// master
	//SimpleStack<T> SS;	// slave
	//SimpleStack<T> SB;	// backup, for getMax
	DequeEx<T> Q;
	typedef struct _E
	{
		T key;
		int counter;
		_E() {}
		_E(T const& key, int counter) : key(key), counter(counter) {}
		_E& operator=(_E const& rhs)
		{
			key = rhs.key;
			counter = rhs.counter;
			return *this;
		}
	}E, *PE;
	DequeEx<E> QQ;
};

int main(int argc, char* argv[])
{
	int n;
	if (scanf("%d\n", &n) == EOF)
		return 1;

	//return (n & 0xff) + 1;
	if (n == 0)
		return 0;

	char op;
	int x;
	Tunel<int> tunel;
	for (int i = 0; i < n; i++) {
		//if (scanf("%c", &op) == EOF)
		//scanf("%c", &op);
		//	return 1;
		do {
			if (scanf("%c", &op) == EOF)
				return 1;
		}while(op != 'D' && op != 'E' && op != 'M');

		switch (op) {
			case 'E':
				if (scanf("%d\n", &x) == EOF)
					return 1;
				tunel.enqueue(x);
				break;
			case 'D':
				printf("%d\n", tunel.dequeue());
				//i++;
				break;
			case 'M':
				printf("%d\n", tunel.getMax());
				//i++;
				break;
			default:
				return 3;
				break;
		}
	}
	return 0;
}
