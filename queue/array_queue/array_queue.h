/** \file array_queue.h
 *
 * Structure definitions, macros, and function declarations for
 * queue implemented in array.
 */

#ifndef _ARRAY_QUEUE_H
#define _ARRAY_QUEUE_H

#include <stdlib.h>
#include <sys/types.h>
#include "../../header.h"

#define CAP    20

typedef int       value_type;
typedef size_t    size_type;

typedef struct {
    value_type    *items;
	size_type      front;
	size_type      rear;
	size_type      size;
	size_type      capacity;
} array_queue;

typedef array_queue    *parray_queue;

parray_queue create_array_queue(void);
parray_queue create_array_queue_n(size_type n);
int enqueue(parray_queue paq, value_type val);
int dequeue(parray_queue paq);
value_type *queue_get_front(parray_queue paq);
int queue_is_empty(parray_queue paq);
void clear_queue(parray_queue paq);
void free_array_queue(parray_queue paq);
size_type queue_size(parray_queue paq);

#endif
