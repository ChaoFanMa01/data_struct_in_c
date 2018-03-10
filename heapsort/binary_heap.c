#include <time.h>
#include <unistd.h>
#include "binary_heap.h"

pb_heap
create_heap(size_type n) {
    pb_heap pbh;

	if ((pbh = malloc(sizeof(binary_heap) + 
	                  sizeof(value_type) * (n - 1))) == NULL)
	    error_null("memory error");
	pbh->array_size = n;
	pbh->heap_length = 0;

	return pbh;
}

size_type
parent(size_type node) {
    return node / 2;
}

size_type
left(size_type node) {
    return 2 * node;
}

size_type 
right(size_type node) {
    return 2 * node + 1;
}

void
swap(pb_heap pbh, size_type a, size_type b) {
    value_type temp = pbh->array[a];
	pbh->array[a] = pbh->array[b];
	pbh->array[b] = temp;
}

void
heapify(pb_heap pbh, size_type node) {
    size_type largest;
	if (node < pbh->heap_length / 2 &&
	    pbh->array[node] < pbh->array[left(node)])
	    largest = left(node);
	else
	    largest = node;
	if (node < pbh->heap_length / 2 &&
	    pbh->array[largest] < pbh->array[right(node)])
	    largest = right(node);
	if (largest != node) {
	    swap(pbh, largest, node);
		heapify(pbh, largest);
	}
}

void
print_bheap(pb_heap pbh) {
    for (size_type i = 0; i < pbh->heap_length; i++)
	    printf("[%d] ", pbh->array[i]);
	printf("\n");
}

void
random_init(pb_heap pbh, size_type n) {
    srand((unsigned)time(NULL));
    if (n > pbh->array_size)
	    return;
	for (size_type i = 0; i < n; i++)
	    pbh->array[i] = rand() % 100;
	pbh->heap_length = n;
}

pb_heap
array_create(value_type nums[], 
           size_type b, size_type e) {
    size_type n = e - b + 1;
	pb_heap  pbh;

    if ((pbh = malloc(sizeof(binary_heap) + 
	     sizeof(value_type) * (n - 1))) == NULL)
	    error_null("memory error");
	
	for (size_type i = 0, j = b; i < n; i++, j++)
	    pbh->array[i] = nums[j];
	pbh->array_size = n;
	pbh->heap_length = n;

	return pbh;
}

void
build_max_heap(pb_heap pbh) {
	for (size_type i = pbh->heap_length / 2; i >= 0; i--) {
	    heapify(pbh, i);
	}
}
