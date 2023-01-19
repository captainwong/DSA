#include "pq_complete_bin_heap_as_vector.h"
#include <stdio.h>

int cmp(const heap_node ha, const heap_node hb) {
	const int a = (const int)ha;
	const int b = (const int)hb;
	return a < b;
}

void print_heap(heap* h) {
	if (h->size == 0) {
		printf("heap empty\n");
	} else {
		printf("heap size=%zi, elems=", h->size);
		for (size_t i = 0; i < h->size; i++) {
			printf("%d, ", (int)(h->elems[i]));
		}
		printf("\n");
	}
}

int main()
{
	heap* h = heap_create();
	heap_init(h);
	for (int i = 0; i < 7; i++) {
		printf("inserting %d\n", i);
		heap_insert(h, (heap_node)i, cmp);
		print_heap(h);
	}
	printf("\n");
	
	for (int i = 0; i < 7; i++) {
		printf("removing %d\n", i);
		heap_remove(h, (heap_node)i, cmp);
		print_heap(h);
	}
	printf("\n");


	for (int i = 0; i < 7; i++) {
		int val = 6 - i;
		printf("inserting %d\n", val);
		heap_insert(h, (heap_node)val, cmp);
		print_heap(h);
	}
	printf("\n");

	for (int i = 0; i < 7; i++) {
		printf("removing %d\n", i);
		heap_remove(h, (heap_node)i, cmp);
		print_heap(h);
	}


}