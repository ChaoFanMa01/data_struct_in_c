/** \file array_queue.c
 *
 * Function definitions for queue implemented in array.
 */

#include "array_queue.h"

/** \fn parray_queue create_array_queue(void)
 * \brief Create a queue that is implemented in array.
 */
parray_queue
create_array_queue(void) {
    parray_queue paq;

	if ((paq = (parray_queue) malloc(sizeof (array_queue)))
	     == NULL)
		 error_null("memory error: create_array_queue()");
    if ((paq->items = (value_type *) malloc(
	     sizeof(value_type) * CAP)) == NULL) {
	    free(paq);
		error_null("memory error: create_array_queue()");
	}
	paq->capacity = CAP;
	paq->size = 0;
	paq->front = paq->capacity / 2;
	paq->rear = paq->capacity / 2;
	return paq;
}

/** \fn parray_queue create_array_queue_n(size_type n)
 * \brief Create an array queue with given capacity.
 */
parray_queue
create_array_queue_n(size_type n) {
    parray_queue paq;

	if ((paq = (parray_queue) malloc(sizeof(array_queue)))
	     == NULL)
	    error_null("memory error: create_array_queue_n()");
	if ((paq->items = (value_type *) malloc(sizeof(value_type) * n))
	     == NULL) {
	    free(paq);
		error_null("memory error: create_array_queue_n()");
	}
	paq->capacity = n;
	paq->size = 0;
	paq->front = paq->capacity / 2;
	paq->rear = paq->capacity / 2;
	return paq;
}

/** \fn int enqueue(parray_queue paq, value_type val)
 *
 * Put a value at the end of a queue.
 * \param paq An array queue.
 * \param val New value.
 * \return Returns -1 on error, 0 otherwise.
 */
int
enqueue(parray_queue paq, value_type val) {
    if (paq == NULL || paq->size >= paq->capacity)
	    return ERROR;
	*(paq->items + paq->rear) = val;
	if (paq->rear == paq->capacity - 1) {
	    paq->rear = 0;
	} else {
	    paq->rear++;
	}
	paq->size++;
	return OK;
}

/** \fn int dequeue(parray_queue paq)
 * 
 * Delete the value at the end of a queue.
 * \param paq An array queue.
 * \return Returns -1 on error, 0 otherwise.
 */
int
dequeue(parray_queue paq) {
    if (paq == NULL || paq->size == 0)
	    return ERROR;
	if (paq->front == paq->capacity - 1) {
	    paq->front = 0;
	} else {
	    paq->front++;
	}
	paq->size--;
	return OK;
}

/** value_type * get_front(parray_queue paq)
 * \brief Get the front value of a queue.
 * 
 * \param paq An array queue.
 * \return Returns the address of the front element.
 */
value_type *
get_front(parray_queue paq) {
    if (paq == NULL || paq->size == 0)
	    return NULL;
	return paq->items + paq->front;
}

/** \fn int is_empty(parray_queue paq)
 * \brief Check whether a queue is empty.
 * 
 * \return Returns 1 on empty, 0 otherwise.
 */
int
is_empty(parray_queue paq) {
    if (paq == NULL || paq->size == 0)
	    return TRUE;
	return FALSE;
}

/** \fn void clear(parray_queue paq)
 * \brief Clear a queue.
 */
void
clear(parray_queue paq) {
    if (paq == NULL)
	    return;
    paq->size = 0;
	paq->front = paq->capacity / 2;
	paq->rear = paq->capacity / 2;
}

/** \fn void free_array_queue(parray_queue paq)
 * \brief Free the memory occupied by an array queue.
 */
void
free_array_queue(parray_queue paq) {
    if (paq == NULL)
	    return;
	if (paq->items != NULL)
	    free(paq->items);
	free(paq);
}

/** \fn size_type size(parray_queue paq)
 * \brief Return the size of a queue.
 *
 * \param paq A queue.
 * \return Returns -1 on error, non-negative integer otherwise.
 */
size_type
size(parray_queue paq) {
    if (paq == NULL)
	    return -1;
	return paq->size;
}
