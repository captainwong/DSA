#pragma once

#include <stddef.h> // size_t

/*
priority queue 
a complete binary heap, implemented by vector.
the root (elem[0]) is always the min node, the height of the tree is at most log2(nodes).
*/


typedef void* heap_node;
typedef struct heap_s heap;

struct heap_s {
	heap_node* elems;
	size_t size, capacity;
};


// return non-zero if a < b
typedef int(*heap_compare_fn)(const heap_node a, const heap_node b);

heap* heap_create();
void heap_init(heap* h);
heap_node heap_min(heap* h);
// return 0 for success
// return -1 for fail
int heap_insert(heap* h, heap_node new_node, heap_compare_fn less_than);
void heap_remove(heap* h, heap_node node, heap_compare_fn less_than);


