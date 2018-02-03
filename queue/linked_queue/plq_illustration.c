/** \file plq_illustration.c
 *
 * Function definitions for illustrating how to use 
 * link implemented queue.
 */

#include "plq_illustration.h"

/** \fn void print_queue(plinked_queue plq)
 * \brief Print values storing in a queue.
 */
void
print_queue(plinked_queue plq) {
    if (plq == NULL || plq->front == NULL)
	    return;
	print_line(plq->size);
	for (plq_node node = plq->front; node != NULL; 
	     node = node->next) {
	    if (node == plq->front)
		    print_int_red(node->item);
		else if (node == plq->rear)
		    print_int_white(node->item);
		else
		    print_int_default(node->item);
	}
	printf("\n");
	print_line(plq->size);
}

/** \fn void print_line(size_type n)
 * \brief Print a line.
 */
void
print_line(size_type n) {
    for (size_type i = 0; i < n; i++)
	    for (size_type j = 0; j < 8; j++)
		    if (j < 5)
			    printf("-");
			else
			    printf(" ");
	printf("\n");
}
