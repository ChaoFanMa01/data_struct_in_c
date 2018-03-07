/** \file stack.h
 * Structure defintions, macros, and function declarations
 * for stack.
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <sys/types.h>
#include "../header.h"

#define INIT_CAP    10


typedef struct {
    value_type    *items;     /**< Values stored in this stack */
	size_type      top;      /**< The top of this stack */
	size_type      capacity;  /**< The number of values may be 
	                               stored in this stack */
} stack;

typedef stack *pstack;

pstack create_stack(void);
pstack create_stack_n(size_type n);
int push(pstack ps, value_type val);
int pop(pstack ps);
int stack_is_empty(pstack ps);
size_type stack_size(pstack ps);
value_type *get_top(pstack ps);
void clear_stack(pstack ps);
void free_stack(pstack ps);
#endif
