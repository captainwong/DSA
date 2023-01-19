#include "pq_complete_bin_heap_as_vector.h"
#include <stdlib.h>

#define DEFAULT_CAPACITY 16

static inline size_t parent(size_t i)
{
	return (i - 1) >> 1;
}

static inline size_t lchild(size_t i)
{
	return (i << 1) + 1;
}

static inline size_t rchild(size_t i)
{
	return (i + 1) << 1;
}

// return non-zero if i in heap
static inline int inheap(heap* h, size_t i)
{
	return 0 <= i && i < h->size;
}

// return non-zero if i has left child
static inline int has_lchild(heap* h, size_t i)
{
	return inheap(h, lchild(i));
}

// return non-zero if i has right child
static inline int has_rchild(heap* h, size_t i)
{
	return inheap(h, rchild(i));
}

static inline size_t lesser(heap* h, size_t i, size_t j, heap_compare_fn less_than)
{
	return less_than(h->elems[i], h->elems[j]) ? i : j;
}

// return the lesser index between i and i's children
static inline size_t proper_parent(heap* h, size_t i, heap_compare_fn less_than)
{
	if (has_rchild(h, i)) {
		return lesser(h, rchild(i), lesser(h, i, lchild(i), less_than), less_than);
	} else if (has_lchild(h, i)) {
		return lesser(h, i, lchild(i), less_than);
	} else {
		return i;
	}
}

static inline void swap(heap_node* a, heap_node* b)
{
	heap_node t = *a;
	*a = *b;
	*b = t;
}

// return 0 if success
static int vector_push(heap* h, heap_node node)
{
	if (h->size + 1 < h->capacity) { // not full
		h->elems[h->size++] = node;
		return 0; 
	}

	if (h->capacity == 0) {
		h->capacity = DEFAULT_CAPACITY;
	} else {
		h->capacity <<= 1;
	}
	
	heap_node* elems = realloc(h->elems, h->capacity * sizeof(heap_node));
	if (!elems) {
		return -1;
	}
	h->elems = elems;
	h->elems[h->size++] = node;
	return 0;
}

static void vector_shrink(heap* h)
{
	if (h->capacity <= DEFAULT_CAPACITY || h->size * 2 < h->capacity) {
		return;
	}
	h->capacity >>= 1;
	heap_node* elems = realloc(h->elems, h->capacity * sizeof(heap_node));
	if (!elems) {
		h->capacity <<= 1;
		return;
	}
	h->elems = elems;
}

static void percolate_up(heap* h, size_t i, heap_compare_fn less_than)
{
	while (i > 0) {
		size_t j = parent(i);
		if (less_than(h->elems[j], h->elems[i])) {
			// parent node is less-than child, no need to walk up
			break;
		}
		swap(&h->elems[i], &h->elems[j]);
		i = j;
	}
}

static void percolate_dn(heap* h, size_t i, heap_compare_fn less_than)
{
	for (size_t j = proper_parent(h, i, less_than); i != j; ) {
		swap(&h->elems[i], &h->elems[j]);
		i = j;
		j = proper_parent(h, i, less_than);
	}
}

heap* heap_create()
{
	heap* h = malloc(sizeof(*h));
	if (!h) return NULL;
	return h;
}

void heap_init(heap* h)
{
	h->elems = NULL;
	h->size = 0;
	h->capacity = 0;
}

heap_node heap_min(heap* h)
{
	return h->size > 0 ? h->elems[0] : NULL;
}

int heap_insert(heap* h, heap_node new_node, heap_compare_fn less_than)
{
	// push back to vector
	if (0 != vector_push(h, new_node)) {
		return -1;
	}
	percolate_up(h, h->size - 1, less_than);
	return 0;
}

void heap_remove(heap* h, heap_node node, heap_compare_fn less_than)
{
	size_t nid = 0;
	while (nid < h->size && h->elems[nid] != node) { // find node's idx
		nid++;
	}
	swap(&h->elems[--h->size], &h->elems[nid]);
	percolate_dn(h, nid, less_than);
	percolate_up(h, nid, less_than);
	vector_shrink(h);
}


















