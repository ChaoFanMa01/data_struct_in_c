/** \file linked_queue.c
 *
 * Function definitions for queue implemented in linked list.
 */

#include "linked_queue.h"

/** \fn plq_node create_lq_node(value_type val)
 * \brief Create a node for link implemented queue.
 */
plq_node
create_lq_node(value_type val) {
    plq_node node;

	if ((node = (plq_node) malloc(sizeof(struct lq_node)))
	     == NULL)
	    error_null("memory error: create_lq_node()");
	node->item = val;
	node->next = NULL;
	return node;
}

/** \fn plinked_queue create_linked_queue(void)
 * \brief Create a link implemented queue.
 */
plinked_queue
create_linked_queue(void) {
    plinked_queue plq;

    if ((plq = (plinked_queue) malloc(
	     sizeof (struct linked_queue))) == NULL)
	    error_null("memory error: create_linked_queue()");
	plq->front = NULL;
	plq->rear = NULL;
	plq->size = 0;
	return plq;
}

/** \fn int enqueue(plinked_queue plq, value_type val)
 *
 * Put a new node containing given value at the rear of
 * a queue.
 * \param plq A link implemented queue.
 * \param val Given value.
 * \return Returns -1 on error, 0 otherwise.
 */
int
enqueue(plinked_queue plq, value_type val) {
    plq_node node;
    if (plq == NULL)
	    return ERROR;
    if ((node = create_lq_node(val)) == NULL)
	    return ERROR;
	if (plq->rear == NULL && plq->front == NULL) {
	    plq->front = node;
		plq->rear = node;
	} else {
	    plq->rear->next = node;
		plq->rear = node;
	}
	plq->size++;
	return OK;
}

/** \fn int dequeue(plinked_quque plq)
 *
 * Remove the front node from a queue.
 */
int
dequeue(plinked_queue plq) {
    plq_node node;
	if (plq == NULL || plq->front == NULL || plq->rear == NULL)
	    return ERROR;
	node = plq->front;
	if (plq->rear == plq->front) {
	    plq->rear = NULL;
		plq->front = NULL;
	} else {
	    plq->front = plq->front->next;
	}
	free(node);
	plq->size--;
	return OK;
}

/** \fn value_type *get_front(plinked_queue plq)
 * \brief Return the address of the value contained in the
 * front node of a queue.
 */
value_type *
get_front(plinked_queue plq) {
    if (plq == NULL || plq->front == NULL)
	    return NULL;
	return &plq->front->item;
}

/** \fn int is_empty(plinked_queue plq)
 * \brief Check whether a queue is empty.
 *
 * \return Returns 1 if empty, 0 otherwise.
 */
int
is_empty(plinked_queue plq) {
    if (plq->size == 0)
	    return TRUE;
	return FALSE;
}

/** \fn int clear(plinked_queue plq)
 * \brief Clear the memory occupied by the nodes of a queue.
 */
int 
clear(plinked_queue plq) {
    plq_node node, temp;

	if (plq == NULL || plq->front == NULL)
	    return ERROR;
	for (node = plq->front; node != NULL; ) {
	    temp = node->next;
		free(node);
		node = temp;
	}
	plq->front = NULL;
	plq->rear = NULL;
	plq->size = 0;
	return OK;
}

/** \fn void free_linked_queue(plinked_queue plq)
 * \brief Free a queue.
 */
void
free_linked_queue(plinked_queue plq) {
    if (plq == NULL)
	    return;
	clear(plq);
	free(plq);
}

/** \fn size_type size(plinked_queue plq)
 * \brief Return the size of a queue.
 */
size_type
size(plinked_queue plq) {
    return plq->size;
}
