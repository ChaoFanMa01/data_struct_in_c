/** \file aq_illustration.c
 *
 * Function definitions for illustrating how to use 
 * array implemented queue.
 */
#include "aq_illustration.h"

/** \fn void print_queue(parray_queue paq)
 * \brief Print values storing in a queue.
 */
void
print_queue(parray_queue paq) {
    if (paq == NULL || paq->size == 0)
	    return;
	print_line(paq->size);
	for (size_type i = 0; i < paq->capacity; i++)
	    if (paq->front < paq->rear) {
		    if (i < paq->front || i >= paq->rear)
			    print_empty();
			else if (i == paq->front)
			    print_int_red(*(paq->items + i));
			else if (i == paq->rear - 1)
			    print_int_white(*(paq->items + i));
			else 
			    print_int_default(*(paq->items + i));
		} else {
		    if (i >= paq->rear && i < paq->front)
			    print_empty();
			else if (i == paq->front)
			    print_int_red(*(paq->items + i));
			else if (i == paq->rear - 1)
			    print_int_white(*(paq->items + i));
			else
			    print_int_default(*(paq->items + i));
		}
	printf("\n");
	print_line(paq->size);
}

/** \fn void print_line(size_type n)
 * \brief Print a line.
 */
void
print_line(size_type n) {
    for (size_type i = 0; i < n; i++)
	    for (size_type j = 0; j < 5; j++)
			printf("-");
	printf("\n");
}
