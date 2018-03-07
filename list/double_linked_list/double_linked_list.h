/** \file double_linked_list.h
 * 
 * Macros, type definitions, and function
 * declarations for double linked list.
 */

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stdlib.h>
#include <sys/types.h>
#include "../../header.h"


typedef struct dlinked_list_node dll_node;
typedef struct dlinked_list_node *pdll_node;

struct dlinked_list_node {
    value_type    item;    /**< The data stored in this node */
	pdll_node     next;    /**< The pointer to next node */
	pdll_node     prev;    /**< The pointer to previous node */
};

typedef struct {
    pdll_node    head;    /**< The first node of this list */
	size_type    size;    /**< The current size of this list */
} dlinked_list;

typedef dlinked_list *pdlinked_list;

pdll_node create_dlinked_list_node(value_type val);
pdlinked_list create_dlinked_list(void);
static pdll_node find_node(pdlinked_list pdll, value_type val, int (*cmp)(value_type, value_type));
size_type get_index(pdlinked_list pdll, value_type val, int (*cmp)(value_type, value_type));
int insert_after(pdlinked_list pdll, value_type pos, value_type val, int (*cmp)(value_type, value_type));
int insert_before(pdlinked_list pdll, value_type pos, value_type val, int (*cmp)(value_type, value_type));
int insert_head(pdlinked_list pdll, value_type val);
int insert_tail(pdlinked_list pdll, value_type val);
int delete_value(pdlinked_list pdll, value_type val, int (*cmp)(value_type, value_type));
int is_empty(pdlinked_list pdll);
void free_dlinked_list(pdlinked_list pdll);
void clear(pdlinked_list pdll);
size_type size_of_dlinked_list(pdlinked_list pdll);
#endif
