#include <stdio.h>
#include <stdlib.h>

template <typename t>
void swap(t& a, t& b)
{
	t t = a;
	a = b;
	b = t;
}

#include "../include/vector.h"

int main(int argc, char* argv[])
{
	/*Fibnacci f(0);

	for (int i = 0; i < 100; i++, f.next()) {
		printf("Fib(%05d) = %22I64d\n", i, f.get());
	}*/

	Vector<int> vector;
	vector.insert(1);
	vector.insert(3);
	vector.insert(2);
	vector.insert(4);
	vector.insert(5);
	vector.insert(1);
	vector.insert(1);

	int size = vector.size();
	printf("Initialize:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	vector.sort();
	printf("Sorted:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	
	vector.uniquify();
	size = vector.size();
	printf("Uniquified:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	getchar();
	return 0;
}