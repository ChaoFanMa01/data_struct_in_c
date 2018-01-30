/** \file linked_list.c
 *
 * Function definitions for linked list.
 */

#include "linked_list.h"

/** \fn plinked_list create_linked_list(void)
 * \brief Create an empty linked list.
 *
 * \return Return null pointer on error, non-null
 *         pointer otherwise.
 */
plinked_list 
create_linked_list(void) {
    plinked_list pll;

	if ((pll = (plinked_list) malloc(sizeof(linked_list)))
	    == NULL)
		error_null("memory error: create_linked_list()");
	pll->head = NULL;
	pll->size = 0;
	return pll;
}

/** \fn pll_node create_linked_list_node(value_type val)
 * \brief Create an empty linked list node.
 *
 * \return Return null pointer on error, non-null 
 *         pointer otherwise.
 */
pll_node 
create_linked_list_node(value_type val) {
    pll_node pn;

	if ((pn = (pll_node) malloc(sizeof(ll_node))) == NULL)
	    error_null("memory error: create_linked_list_node()");
	pn->item = val;
	pn->next = NULL;
	return pn;
}

/** \fn static int insert_after(plinked_list pll, pll_node node, pll_node position)
 *
 * Insert a node after given position (node).
 * \param node The node to be inserted.
 * \param position Where the node to be inserted.
 * \return Return -1 on error, 0 otherwise.
 */
static int
insert_after(plinked_list pll, pll_node node, pll_node position) {
    if (node == NULL || position == NULL)
	    error_negative("parameter error: insert_before()");
	node->next = position->next;
	position->next = node;
	pll->size++;
	return OK;
}

/** \fn static pll_node find_previous(plinked_list pll, value_type val, int (*cmp)(value_type, value_type))
 * 
 * Find a node, which is one position previous to the
 * node containing given value, from a linked list.
 * \param pll A linked list.
 * \param val Given value.
 * \param cmp The comparision function that is used to 
 *        compare two values. If this parameter is set 
 *        to NULL, '==' sign is used to compare two values.
 * \return Return null pointer if no such node or this value
 *         is contained in the head of this list (it is up 
 *         to the caller to check which condition occurs), 
 *         non-null pointer otherwise.
 */
static pll_node
find_previous(plinked_list pll, value_type val,
              int (*cmp)(value_type, value_type)) {
	pll_node pn;
	if (pll == NULL)
	    error_null("parameter error: find_previous()");
	for (pn = pll->head; pn != NULL &&
	     pn->next != NULL; pn = pn->next)
		 if (cmp != NULL) {
		     if (cmp(pn->next->item, val) == 0)
			     return pn;
		 } else {
		     if (pn->next->item == val)
			     return pn;
		 }
	return NULL;
}

/** \fn size_type get_index(plinked_list pll, value_type val, int (*cmp)(value_type, value_type))
 * \brief Get the index of a given value from a linked list.
 * \param pll A linked list.
 * \param val Given value.
 * \param cmp The callback function used to compare.
 * \return Return non-negative integer on success, negative
 *         integer otherwise.
 */
size_type
get_index(plinked_list pll, value_type val,
          int (*cmp)(value_type, value_type)) {
    size_type index = 0;
	if (pll == NULL || pll->head == NULL)
	    return ERROR;
	if (cmp == NULL) {
	    for (pll_node nd = pll->head; nd != NULL;
		     nd = nd->next, index++)
	        if (val == nd->item) 
			    return index;
	} else {
	    for (pll_node nd = pll->head; nd != NULL;
		     nd = nd->next, index++)
		    if (cmp(val, nd->item) == 0)
			    return index;
	}
	return ERROR;
}

/** \fn  int is_linked_list_head(plinked_list pll, value_type val, int (*cmp)(value_type v1, value_type v2))
 * 
 * Check whether given value exists at the head of this
 * linked list.
 * \param pll A linked list.
 * \param val Given value.
 * \param cmp The comparison function.
 * \return Return 1 if is, 0 otherwise.
 */
int
is_linked_list_head(plinked_list pll, value_type val,
    int (*cmp)(value_type v1, value_type v2)) {
	if (pll == NULL || pll->head == NULL)
	    return FALSE;
    if (cmp == NULL) {
	    if (pll->head->item == val)
		    return TRUE;
		else
		    return FALSE;
	} else {
	    if (cmp(pll->head->item, val) == 0)
		    return TRUE;
		else
		    return FALSE;
	}
}

/** \fn static int insert_head(plinked_list pll, pll_node node)
 * \brief Insert a node at the head of this linked list.
 * \param pll A linked list.
 * \param node The node to be inserted.
 * \return Return -1 on error, 0 otherwise.
 */
static int
insert_head(plinked_list pll, pll_node node) {
    if (pll == NULL || node == NULL)
	    return ERROR;
	node->next = pll->head;
	pll->head = node;
	pll->size++;
	return OK;
}

/** \fn int is_empty_linked_list(plinked_list pll)
 * \brief Check whether a linked list is empty.
 * \param pll A linked list.
 * \return Return 1 on is, 0 otherwise.
 */
int
is_empty_linked_list(plinked_list pll) {
    if (pll == NULL || pll->head == NULL)
	    return TRUE;
	return FALSE;
}

/** \fn static int insert_tail(plinked_list pll, pll_node node)
 * \brief Insert a new node to the end of a linked list.
 * \param pll A linked list.
 * \param node The node to be inserted.
 * \return Return -1 on error, 0 otherwise.
 */
static int
insert_tail(plinked_list pll, pll_node node) {
    pll_node nd;
    if (pll == NULL)
	    return ERROR;
	if (is_empty_linked_list(pll) == TRUE) {
	    return insert_head(pll, node);
	} else {
	    for (nd = pll->head; nd->next != NULL; nd = nd->next) ;
		return insert_after(pll, node, nd);
	}
}

/** \fn int insert_linked_list_head(plinked_list pll, value_type val)
 * \brief Insert a value to the head of a linked list.
 * \param pll A linked list.
 * \param val The value to be inserted.
 * \return Return -1 on error, 0 otherwise.
 */
int 
insert_linked_list_head(plinked_list pll, value_type val) {
    pll_node node;
	if (pll == NULL)
	    return ERROR;
	if ((node = create_linked_list_node(val)) == NULL)
	    return ERROR;
	if (insert_head(pll, node) == ERROR) {
	    free(node);
		return ERROR;
	}
	return OK;
}

/** \fn int insert_linked_list_tail(plinked_list pll, value_type val)
 * \brief Insert a value to the end of a linked list.
 * \param pll A linked list.
 * \param val The value to be inserted.
 * \return Return -1 on error, 0 otherwise.
 */
int
insert_linked_list_tail(plinked_list pll, value_type val) {
    pll_node node;
	if (pll == NULL)
	    return ERROR;
	if ((node = create_linked_list_node(val)) == NULL)
	    return ERROR;
	if (insert_tail(pll, node) == ERROR) {
	    free(node);
		return ERROR;
	}
	return OK;
}

/** \fn int insert(plinked_list pll, value_type val, value_type pos, int (*cmp)(value_type, value_type))
 *
 * Insert a value to a linked list.
 * \param pll A linked list.
 * \param val The value to be inserted.
 * \param pos The new value will be inserted before
 *        the pos parameter.
 * \param cmp The callback function used to compare
 *        two value, returning 0 when equal, 1 when 
 *        v1 is larger than v2, -1 otherwise.
 * \return Return -1 on insertion error, 0 otherwise.
 */
int
insert(plinked_list pll, value_type val, value_type pos,
       int (*cmp)(value_type v1, value_type v2)) {
    pll_node node, new_node;

	if ((new_node = create_linked_list_node(val)) == NULL)
	    return ERROR;
	if (is_linked_list_head(pll, pos, cmp) == TRUE) {
	    if (insert_head(pll, new_node) == OK)
		    return OK;
	} else {
	    if ((node = find_previous(pll, pos, cmp)) != NULL)
		    if (insert_after(pll, new_node, node) == OK)
			    return OK;
	}
	free(new_node);
	return ERROR;
}

/** \fn void free_linked_list(plinked_list pll)
 * \brief Free memory used by linked list.
 */
void
free_linked_list(plinked_list pll) {
    if (pll == NULL)
	    return;
    for (pll_node node = pll->head, nd; node != NULL;) {
	    nd = node->next;
		free(node);
		node = nd;
	}
	free(pll);
}

/** \fn int delete_value(plinked_list pll, value_type val, int (*cmp)(value_type, value_type))
 * \brief Delete a value from a linked list.
 * \param pll A linked list.
 * \param val Given value.
 * \param cmp The callback function used for comparison.
 * \return Return -1 on failure, 0 otherwise.
 */
int
delete_value(plinked_list pll, value_type val,
             int (*cmp)(value_type, value_type)) {
	if (pll == NULL || pll->head == NULL)
	    return ERROR;
    if (is_linked_list_head(pll, val, cmp) == TRUE) {
	    pll_node nd = pll->head;
		pll->head = pll->head->next;
		free(nd);
		pll->size--;
		return OK;
	} else {
	    pll_node nd, node;
		if ((nd = find_previous(pll, val, cmp)) == NULL)
		    return ERROR;
		node = nd->next;
		nd->next = nd->next->next;
		free(node);
		pll->size--;
		return OK;
	}
}

/** \fn int is_empty(plinked_list pll)
 * \brief Check whether a linked list is empty.
 * \return Return 1 on empty, 0 otherwise.
 */
int
is_empty(plinked_list pll) {
    if (pll->size == 0)
	    return TRUE;
	return FALSE;
}

/** \fn void clear(plinked_list pll)
 * \brief Clear a linked list.
 */
void
clear(plinked_list pll) {
    pll_node nd;
	if (pll == NULL || pll->head == NULL)
	    return;
	for (pll_node node = pll->head; node != NULL;) {
	    nd = node->next;
		free(node);
		node = nd;
	}
	pll->head = NULL;
	pll->size = 0;
}

/** \fn size_type size_of_linked_list(plinked_list pll)
 * \brief Return the current size of a linked list.
 */
size_type
size_of_linked_list(plinked_list pll) {
    if (pll == NULL)
	    return ERROR;
	return pll->size;
}
