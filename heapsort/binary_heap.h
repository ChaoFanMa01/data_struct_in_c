#ifndef _BINARY_HEAP_H
#define _BINARY_HEAP_H

#include "../header.h"

typedef struct {
    size_type    array_size;
	size_type    heap_length;
	value_type   array[1];
} binary_heap;

typedef binary_heap *pb_heap;

pb_heap create_heap(size_type n);
size_type parent(size_type node);
size_type left(size_type node);
size_type right(size_type node);
void swap(pb_heap pbh, size_type a, size_type b);
void heapify(pb_heap pbh, size_type node);
void print_bheap(pb_heap pbh);
void random_init(pb_heap pbh, size_type n);
void build_max_heap(pb_heap pbh);
pb_heap array_create(value_type nums[], size_type b, size_type e);

#endif
