/** \file double_linked_list.c
 *
 * Function definitions for double linked list.
 */

#include "double_linked_list.h"

/** \fn pdll_node create_dlinked_list_node(value_type val)
 * \brief Create a double linked list node with given value.
 *
 * \param val Given value.
 * \return Returns null pointer on error, a non-null pointer
 *         otherwise.
 */
pdll_node 
create_dlinked_list_node(value_type val) {
    pdll_node node;

	if ((node = (pdll_node) malloc(sizeof(dll_node))) == NULL)
	    error_null("memory error: create_dlinked_list_node()");
	
	node->item = val;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

/** \fn pdlinked_list create_dlinked_list(void)
 * \brief Create a double linked list.
 *
 * \return Returns null pointer on error, a non-null pointer
 *         otherwise.
 */
pdlinked_list
create_dlinked_list(void) {
    pdlinked_list pdll;

	if ((pdll = (pdlinked_list) malloc(sizeof(dlinked_list)))
	     == NULL)
	    error_null("memory error: create_dlinked_list()");
	
	pdll->head = NULL;
	pdll->size = 0;
	return pdll;
}

/** \fn static pdll_node find_node(pdlinked_list pdll, value_type val,int (*cmp)(value_type, value_type))
 *
 * Find a node that contains the value given by the second parameter
 * from a double linked list.
 * \param pdll A double linked list.
 * \param val Given value.
 * \param cmp A function used to compare values, i.e., returns 0 when
 *        two values are equal, -1 when the first is smaller than the
 *        second, or 1 when the first is greater than the second.
 * \return Returns null pointer when fails to find, a non-null
 *         pointer otherwise.
 */
static pdll_node
find_node(pdlinked_list pdll, value_type val,
          int (*cmp)(value_type, value_type)) {
    if (pdll == NULL || pdll->head == NULL)
	    return NULL;
    for (pdll_node node = pdll->head; node != NULL; 
	     node = node->next)
        if (cmp == NULL) {
		    if (node->item == val)
			    return node;
		} else {
		    if (cmp(val, node->item) == 0)
			    return node;
		}
    return NULL;
}

/** \fn size_type get_index(pdlinked_list pdll, value_type val, int (*cmp)(value_type, value_type))
 *
 * Get the index of the first node containing given value from a 
 * double linked list.
 * \param pdll A double linked list.
 * \param val Given value.
 * \param cmp A function used to compare two values.
 * \return Returns -1 when fails to find this node, a non-negative
 *         integer otherwise.
 */
size_type
get_index(pdlinked_list pdll, value_type val,
          int (*cmp)(value_type, value_type)) {
    size_type index = 0;
	if (pdll == NULL || pdll->head == NULL)
	    return ERROR;
	if (cmp == NULL) {
	    for (pdll_node node = pdll->head; node != NULL;
		     node = node->next, index++)
		    if (val == node->item)
			    return index;
	} else {
	    for (pdll_node node = pdll->head; node != NULL;
		     node = node->next, index++)
		    if (cmp(val, node->item) == 0)
			    return index;
	}
	return ERROR;
}

/** \fn int insert_after(pdlinked_list pdll, value_type pos, value_type val, int (*cmp)(value_type, value_type))
 *
 * Insert a new node with given value after a node containing the 
 * value given by parameter pos in a double linked list.
 * \param pdll A double linked list.
 * \param pos The value of the node where new node to be inserted
 *            after.
 * \param val The value of the new node.
 * \param cmp The function used to compare two values.
 * \return Returns -1 on error, 0 otherwise.
 */
int
insert_after(pdlinked_list pdll, value_type pos, value_type val,
             int (*cmp)(value_type, value_type)) {
    pdll_node node, temp;
	if ((node = find_node(pdll, pos, cmp)) == NULL)
	    return ERROR;
    if ((temp = create_dlinked_list_node(val)) == NULL)
	    return ERROR;
	// if node is the tail of this list.
	if (node->next == NULL) {
	    temp->prev = node;
		node->next = temp;
	} else { 
	// otherwise.
	    temp->next = node->next;
	    temp->next->prev = temp;
	    temp->prev = node;
	    node->next = temp;
	}
	pdll->size++;

	return OK;
}

/** \fn int insert_before(pdlinked_list pdll, value_type pos, value_type val, int (*cmp)(value_type, value_type))
 *
 * Insert a new node with given value before a node containing the 
 * value given by parameter pos in a double linked list.
 * \param pdll A double linked list.
 * \param pos The value of the node where new node to be inserted
 *            before.
 * \param val The value of the new node.
 * \param cmp The function used to compare two values.
 * \return Returns -1 on error, 0 otherwise.
 */
int
insert_before(pdlinked_list pdll, value_type pos, value_type val,
              int (*cmp)(value_type, value_type)) {
    pdll_node node, temp;
	if ((node = find_node(pdll, pos, cmp)) == NULL)
	    return ERROR;
	if ((temp = create_dlinked_list_node(val)) == NULL)
	    return ERROR;
	// if node is the head of this list.
    if (node == pdll->head) {
	    temp->next = node;
		node->prev = temp;
		pdll->head = temp;
	} else {
	// otherwise.
	    node->prev->next = temp;
		temp->prev = node->prev;
		temp->next = node;
		node->prev = temp;
	}
	pdll->size++;

    return OK;
}

/** \fn int insert_head(pdlinked_list pdll, value_type val)
 *
 * Insert a new node with given value to the head of a double
 * linked list.
 * \param pdll A double linked list.
 * \param val Given value.
 * \return Returns -1 on error, 0 otherwise.
 */
int
insert_head(pdlinked_list pdll, value_type val) {
    pdll_node node;

	if (pdll == NULL)
	    return ERROR;
	if ((node = create_dlinked_list_node(val)) == NULL)
	    return ERROR;
	if (pdll->head == NULL) {
	    pdll->head = node;
	} else {
	    node->next = pdll->head;
		pdll->head->prev = node;
		pdll->head = node;
	}
	pdll->size++;

	return OK;
}

/** \fn int insert_tail(pdlinked_list pdll, value_type val)
 *
 * Insert a new node with given value at the tail of a double 
 * linked list.
 * \param pdll A double linked list.
 * \param val Given value.
 * \return Returns -1 on error, 0 otherwise.
 */
int 
insert_tail(pdlinked_list pdll, value_type val) {
    pdll_node node, temp;
	if (pdll == NULL)
	    return ERROR;
	if ((temp = create_dlinked_list_node(val)) == NULL)
	    return ERROR;
	if (pdll->head == NULL) {
	    pdll->head = temp;
	} else {
	    for (node = pdll->head; node->next != NULL; 
		     node = node->next);
		node->next = temp;
		temp->prev = node;
	}
	pdll->size++;

	return OK;
}

/** \fn int delete_value(pdlinked_list pdll, value_type val, int (*cmp)(value_type, value_type))
 *
 * Delete the first node with given value from a double linked list.
 * \param pdll A double linked list.
 * \param val Given value.
 * \param cmp A function used to compare two values.
 * \return Return -1 on error, 0 otherwise.
 */
int
delete_value(pdlinked_list pdll, value_type val,
             int (*cmp)(value_type, value_type)) {
    pdll_node node;
    if (pdll == NULL || pdll->head == NULL)
	    return ERROR;
	if ((node = find_node(pdll, val, cmp)) == NULL)
	    return ERROR;
	if (pdll->head == node) {
	    pdll->head = node->next;
		node->next->prev = NULL;
	} else if (node->next == NULL) {
	    node->prev->next = NULL;
	} else {
	    node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node);
	pdll->size--;
	return OK;
}

/** \fn int is_empty(pdlinked_list pdll)
 * \brief Check whether a double linked list is empty.
 * \return Returns 1 on empty, 0 otherwise.
 */
int
is_empty(pdlinked_list pdll) {
    if (pdll->size == 0)
	    return TRUE;
	return FALSE;
}

/** \fn void free_dlinked_list(pdlinked_list pdll)
 * \brief Free memory used by a double linked list.
 */
void
free_dlinked_list(pdlinked_list pdll) {
    if (pdll == NULL)
	    return;
    for (pdll_node node = pdll->head, nd; node != NULL;) {
	    nd = node->next;
		free(node);
		node = nd;
	}
	free(pdll);
}

/** \fn void clear(pdlinked_list pdll)
 * \brief Clear (e.g., free all nodes of) a double linked list.
 */
void
clear(pdlinked_list pdll) {
    pdll_node nd;
	if (pdll == NULL || pdll->head == NULL)
	    return;
	for (pdll_node node = pdll->head; node != NULL;) {
	    nd = node->next;
		free(node);
		node = nd;
	}
	pdll->head = NULL;
	pdll->size = 0;
}

/** \fn size_type size_of_dlinked_list(pdlinked_list pdll)
 * \brief Return the current size of a double linked list.
 */
size_type
size_of_dlinked_list(pdlinked_list pdll) {
    if (pdll == NULL)
	    return ERROR;
	return pdll->size;
}
