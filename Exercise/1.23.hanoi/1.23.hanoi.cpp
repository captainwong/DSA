// 1.23.hanoi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../../include/dtl/stack.h"
#include <assert.h>
#include <stdio.h>

struct Disk {
	int index;

	Disk(int i) : index(i) {}
};

class Tower : public Stack<Disk>
{
public:
	char name = {};

	Tower(int n, char name)
		: name(name) 
	{
		for (int m = n; m > 0; --m) {
			push(Disk(m));
		}
	}

	void print() {
		printf("Tower %c: ", name);

		for (auto i = first(); i->succ; i = i->succ) {
			printf("%d ", i->data.index);
		}

		printf("\n");
	}
};

void move(Tower& a, Tower& b)
{
	if (!b.empty()) {
		assert(a.top().index < b.top().index);
	}

	b.push(a.pop());

	printf("move disk %d from Tower %c to Tower %c\n", b.top().index, a.name, b.name);
}

void hanoi(int n, Tower& x, Tower& y, Tower& z)
{
	if (n < 1) { return; }

	hanoi(n - 1, x, z, y);
	move(x, z);
	hanoi(n - 1, y, x, z);
}

void hanoi(int n)
{
	printf("---------hanoi(%d)-----------\n", n);
	Tower x(n, 'X'); 
	Tower y(0, 'Y'); 
	Tower z(0, 'Z'); 
	x.print(); y.print(); z.print();

	printf("move start\n");

	hanoi(n, x, y, z);

	printf("move end\n");

	x.print(); y.print(); z.print();
}

int main()
{
	hanoi(1);
	hanoi(2);
	hanoi(3);
	hanoi(4);
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
