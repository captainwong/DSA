#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

static const int MAX_VAR = 1000001;

//struct Node
//{
//	int data;
//	Node* pred;
//	Node* succ;
//	Node(int data) :data(data) {}
//	Node(int data, Node* pred, Node* succ) :data(data), pred(pred), succ(succ) {}
//	inline Node* insertA(int data)
//	{
//		Node* node = new Node(data, this, succ);
//		succ->pred = node;
//		succ = node;
//		return node;
//	}
//
//	inline Node* insertB(int data)
//	{
//		Node* node = new Node(data, pred, this);
//		pred->succ = node;
//		pred = node;
//		return node;
//	}
//};
//
//class SimpleList
//{
//private:
//	Node* head;
//	Node* tail;
//	int _size;
//protected:
//	void init()
//	{
//		head = new Node(0, NULL, NULL);
//		tail = new Node(0, NULL, NULL);
//		head->succ = tail;
//		tail->pred = head;
//		_size = 0;
//	}
//
//	void clear()
//	{
//		Node* node = head;
//		for (int i = 0; i < _size; i++) {
//			Node* temp = node;
//			node = node->succ;
//			delete temp;
//		}
//	}
//public:
//	SimpleList() { init(); }
//	~SimpleList() { clear(); }
//	Node* first() const { return head->succ; }
//	Node* last() const { return tail->pred; }
//	int size() const { return _size; }
//	void insert(int data, int rank = 0)
//	{
//		int minval = _size < rank ? _size : rank;
//		Node* node = head;
//		for (int i = 0; i < minval; i++) {
//			node = node->succ;
//		}
//		node->insertA(data);
//		_size++;
//	}
//
//	int remove(int rank)
//	{
//		Node* node = head->succ;
//		int minval = _size < rank ? _size : rank;
//		for (int i = 0; i < minval; i++) {
//			node = node->succ;
//		}
//		node->pred->succ = node->succ;
//		node->succ->pred = node->pred;
//		int data = node->data;
//		delete node;
//		_size--;
//		return data;
//	}
//};

class Stack
{
public:
	//注意：你不能添加更多的public函数或变量,如有需要可添加析构函数
	Stack();
	~Stack();
	bool empty();
	void push(int);
	int pop();
	int top();
private:
	//此处可以扩展
	//SimpleList list;
	int _size;
	int *_elem;
};

Stack::Stack()
{
	_size = 0;
	_elem = new int[MAX_VAR];
}

Stack::~Stack()
{
	delete[] _elem;
}

bool Stack::empty()
{
	//return list.size() == 0;
	return _size == 0;
}

void Stack::push(int value)
{
	//list.insert(value, list.size());
	_elem[_size++] = value;
}

int Stack::pop()
{
	//return list.remove(list.size() - 1);
	return _elem[--_size];
}

int Stack::top()
{
	//return list.last()->data;
	return _elem[_size - 1];
}

// 极值栈的思路来源于课程讨论中farui的思路
// http://www.xuetangx.com/courses/TsinghuaX/30240184X/2014_T2/discussion/forum/i4x-edx-templates-course-Empty/threads/5465ac3ef605abd56600f26b
// 实现方法参考了习题解析[10-19]中最大值栈的实现方法
class ExtremStack
{
public:
	ExtremStack() {}
	~ExtremStack() {}
	void push(int value)
	{
		s1.push(value);
		//while (!s2.empty() && s2.top() > value) {
		//	s2.pop();
		//}

		// s2保存最小值
		if (!s2.empty())
			s2.push(value < s2.top() ? value : s2.top());
		else
			s2.push(value);
	}
	int pop()
	{
		/*int value = s1.pop();
		if (value == s2.top())
			s2.pop();
		if (s2.empty())
			s2.push(value);
		return value;*/
		s2.pop();
		return s1.pop();
	}
	int top()
	{
		return s1.top();
	}
	bool empty()
	{
		return s1.empty();
	}
	int getMin()
	{
		return s2.top();
	}
private:
	Stack s1;
	Stack s2;
};

//class Queue
//{
//public:
//	Queue() {}
//	~Queue() {}
//	void enqueue(int value)
//	{
//		s1.push(value);
//	}
//	int dequeue()
//	{
//		while (!s1.empty()) {
//			s2.push(s1.pop());
//		}
//		return s2.pop();
//	}
//	bool empty()
//	{
//		return s1.empty() && s2.empty();
//	}
//	int front()
//	{
//		while (!s1.empty()) {
//			s2.push(s1.pop());
//		}
//		return s2.top();
//	}
//	int getMin()
//	{
//		while (!s1.empty()) {
//			s2.push(s1.pop());
//		}
//		return s2.getMin();
//	}
//private:
//	ExtremStack s1;
//	ExtremStack s2;
//};

class Queap
{
public:
	Queap();
	void enqueap(int);
	int dequeap();
	int min();
private:
	//Queue q;
	ExtremStack es1;
	ExtremStack es2;
};

Queap::Queap()
{}

void Queap::enqueap(int value)
{
	//s1.push(value);
	//q.enqueue(value);
	//if (q2.empty() || (q2.front() > value)) {
	//	q2.enqueue(value);
	//}
	//while (!q2.empty() && q2.)
	es1.push(value);
}

int Queap::dequeap()
{
	//return q.dequeue();

	// 不能简单地先将栈1转入栈2，此时栈2可能非空
	if (!es2.empty())
		return es2.pop();

	while (!es1.empty()) {
		es2.push(es1.pop());
	}
	return es2.pop();
}

int Queap::min()
{
	//return q.getMin();
	//while (!es1.empty()) {
	//	es2.push(es1.pop());
	//}
	//return es2.getMin();

	// 同deque，此处也不能简单地返回es2的最值，
	// 要考虑栈1与栈2两者是否为空的情况的组合。

	if (es1.empty() && !es2.empty())
		return es2.getMin();
	else if (!es1.empty() && es2.empty())
		return es1.getMin();
	else {
		int min1 = es1.getMin();
		int min2 = es2.getMin();
		return min1 < min2 ? min1 : min2;
	}
}

int main(int /*argc*/, char** /*argv*/)
{
	int n;
	if (scanf("%d\n", &n) == EOF)
		return 0;

	Queap Q;
	char op = 0;
	int value = 0;
	for (int i = 0; i < n; i++) {
		do {
			if (scanf("%c", &op) == EOF) 
				return 1;
		} while (op != 'E' && op != 'M' && op != 'D');

		switch (op) {
			case 'E':
				if (scanf("%d", &value) == EOF)
					return 2;
				Q.enqueap(value);
				break;
			case 'D':
				printf("%d\n", Q.dequeap());
				break;
			case 'M':
				printf("%d\n", Q.min());
				break;
		}
	}
	return 0;
}
