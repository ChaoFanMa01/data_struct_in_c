/** \file linked_queue.h
 *
 * Structure definitions, macros, and function declarations for
 * queue implemented in linked list.
 */

#ifndef _LINKED_QUEUE_H
#define _LINKED_QUEUE_H

#include <stdlib.h>
#include <sys/types.h>
#include "../../header.h"

typedef int    value_type;
typedef size_t size_type;

typedef struct lq_node         *plq_node;

struct lq_node {
    value_type    item;    /**< The value storing in this node */
	plq_node      next;    /**< Pointer to next node */
};

typedef struct linked_queue    *plinked_queue;

struct linked_queue {
    plq_node    front;    /**< The front node of this queue */
	plq_node    rear;     /**< The rear node of this queue */
	size_type   size;     /**< Recording the size of this queue */
};


plq_node create_lq_node(value_type val);
plinked_queue create_linked_queue(void);
int enqueue(plinked_queue plq, value_type val);
int dequeue(plinked_queue plq);
value_type *get_front(plinked_queue plq);
int is_empty(plinked_queue plq);
int clear(plinked_queue plq);
void free_linked_queue(plinked_queue plq);
size_type size(plinked_queue plq);
#endif
