/** \file stack.c
 * Function definitions for stack.
 */

#include "stack.h"

/** \fn pstack create_stack(void)
 * \brief Create a new stack.
 */
pstack
create_stack(void) {
    pstack ps;

	if ((ps = (pstack) malloc(sizeof(stack))) == NULL)
	    error_null("memory error: create_stack()");
	if ((ps->items = (value_type *) malloc(
	     sizeof(value_type) * INIT_CAP)) == NULL) {
		free(ps);
	    error_null("memory error: create_stack()");
	}
	ps->top = 0;
	ps->capacity = INIT_CAP;
	return ps;
}

/** \fn pstack create_stack_n(size_type n)
 * \brief Create a stack with capacity initialized to be n.
 */
pstack
create_stack_n(size_type n) {
    pstack ps;

	if ((ps = (pstack) malloc(sizeof(stack))) == NULL)
	    error_null("memory error: create_stack()");
	if ((ps->items = (value_type *) malloc(
	     sizeof(value_type) * n)) == NULL) {
		free(ps);
	    error_null("memory error: create_stack()");
	}
	ps->top = 0;
	ps->capacity = n;
	return ps;
}

/** \fn int push(pstack ps, value_type val)
 * \brief Push a new value to the top of a stack.
 *
 * \param ps A stack.
 * \param val New value.
 * \return Returns -1 on error, 0 otherwise.
 */
int
push(pstack ps, value_type val) {
    value_type *temp;
    if (ps == NULL)
	    return ERROR;
	if (ps->top >= ps->capacity) {
	    if ((temp = (value_type *) realloc(ps->items, 
		     sizeof(value_type) * ps->capacity * 2)) == NULL)
		    return ERROR;
		ps->items = temp;
		ps->capacity *= 2;
	}
	*(ps->items + ps->top++) = val;
	return OK;
}

/** \fn int pop(pstack ps)
 * \brief Pop the top element from a stack.
 *
 * \return Returns -1 on error, 0 otherwise.
 */
int
pop(pstack ps) {
    if (is_empty(ps) == TRUE)
	    return ERROR;
	ps->top--;
	return OK;
}

/** int  is_empty(pstack ps)
 * \brief Check whether a stack is empty.
 *
 * \return Returns 1 if empty, 0 otherwise.
 */
int 
is_empty(pstack ps) {
    if (ps->top <= 0)
	    return TRUE;
	return FALSE;
}

/** \fn size_type size(pstack ps)
 * \brief Return the number of values currently in a stack.
 */
size_type
size(pstack ps) {
    return ps->top;
}

/** \fn value_type *get_top(pstack ps)
 * \brief Return the address of the top value of a stack.
 *
 * \return Returns null on error, non-null pointer otherwise.
 */
value_type *
get_top(pstack ps) {
    if (is_empty(ps) == TRUE)
		return NULL;
	return ps->items + ps->top - 1;
}

/** \fn void clear(pstack ps)
 * \brief Clear the values in a stack.
 */
void
clear(pstack ps) {
    if (ps == NULL)
	    return;
    ps->top = 0;
}

/** \fn void free_stack(pstack ps)
 * \brief Free the memory occupied by a stack.
 */
void
free_stack(pstack ps) {
    if (ps == NULL)
	    return;
    free(ps->items);
	free(ps);
}
