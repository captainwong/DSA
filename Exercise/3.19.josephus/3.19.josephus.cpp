// 3.19.josephus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>

/***测试用******/
#include <assert.h>
/*****************/

struct node 
{
	int n = 0;
	node* next = nullptr;
	node(int i, node* next_ = nullptr) :n(i), next(next_) {}

	void print() const {
		printf("%d ", n);
		auto p = next;
		while (p && p != this) {
			printf("%d ", p->n);
			p = p->next;
		}
		printf("\n");
	}
};


int josephus(int n, int k)
{
	node* first = new node(0);
	node* cur = first;
	for (int i = 1; i < n; i++) {
		auto p = new node(i, first);
		cur->next = p;
		cur = p;
	}

	cur = first;
	while (n > 1) {
		printf("n=%d k=%d, list is ", n, k); cur->print();
		for (int i = 0; i < k - 2; i++) { // 取前一个
			cur = cur->next;
		}
		auto p = cur->next;
		cur->next = p->next;
		cur = p->next;
		printf("removed %d\n", p->n); delete p;
		n--;
	}

	int lucky_boy = cur->n;
	delete cur;
	printf("lucky boy is %d\n", lucky_boy);
	return lucky_boy;
}

int main()
{
	josephus(10, 7);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
