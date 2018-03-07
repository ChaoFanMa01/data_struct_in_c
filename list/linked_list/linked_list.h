/** \file linked_list.h
 *
 * Macros, type definitions, and function
 * declarations for linked list.
 */

 #ifndef _LINKED_LIST_H
 #define _LINKED_LIST_H

#include <stdlib.h>
#include <sys/types.h>
#include "../../header.h"


typedef struct linked_list_node  ll_node;
typedef struct linked_list_node *pll_node;

struct linked_list_node {
    value_type   item;   /**< The data stored in this node */
	pll_node     next;   /**< The pointer to next node */
};

typedef struct {
    pll_node     head;   /**< The first node of this list */
	size_type    size;   /**< The current size of this list */
} linked_list;

typedef linked_list *plinked_list;

plinked_list create_linked_list(void);
pll_node create_linked_list_node(value_type val);
static int insert_after(plinked_list pll, pll_node node, pll_node position);
static pll_node find_previous(plinked_list pll, value_type val, int (*cmp)(value_type, value_type));
size_type get_index(plinked_list pll, value_type val, int (*cmp)(value_type, value_type));
int is_linked_list_head(plinked_list pll, value_type val, int (*cmp)(value_type v1, value_type v2));
static int insert_head(plinked_list pll, pll_node node);
static int insert_tail(plinked_list pll, pll_node node);
int is_empty_linked_list(plinked_list pll);
int insert_linked_list_head(plinked_list pll, value_type val);
int insert_linked_list_tail(plinked_list pll, value_type val);
int insert(plinked_list pll, value_type val, value_type pos, int (*cmp)(value_type v1, value_type v2));
void free_linked_list(plinked_list pll);
int delete_value(plinked_list pll, value_type val, int (*cmp)(value_type, value_type));
int is_empty(plinked_list pll);
void clear(plinked_list pll);
size_type size_of_linked_list(plinked_list pll);
#endif
