/** \file array_list.c
 * \brief Function definitions for array list.
 */

#include "../../header.h"
#include "array_list.h"


/** \fn parray_list create_array_list(void)
 * \brief Create an empty array list with default
 *        capacity.
 * \return Return NULL on memory allocation error,
 *         a non-NULL pointer otherwise.
 */
parray_list 
create_array_list(void) {
    parray_list pa;

	if ((pa = (parray_list) malloc(sizeof(array_list))) == NULL)
	    error_null("memory allocation error");
	pa->size = 0;
	pa->capacity = INIT_CAP;

	if ((pa->items = (value_type *) malloc(
	    sizeof(value_type) * pa->capacity)) == NULL) {
		free(pa);
		error_null("memory allocation error");
	}
	return pa;
}

/** \fn parray_list create_array_list_n(size_type n)
 * \brief Create an array list with capacity to be n.
 *
 * \param n The given capacity of this array list.
 * \return Return NULL pointer on memory allocation
 *         error, a non-NULL pointer otherwise.
 */
parray_list
create_array_list_n(size_type n) {
    parray_list pa;

	if ((pa = (parray_list) malloc(
	    sizeof(array_list))) == NULL)
		error_null("memory allocation error");
	pa->size = 0;
	pa->capacity = n;

	if ((pa->items = (value_type *) malloc(
	    sizeof(value_type) * pa->capacity)) == NULL) {
		free(pa);
		error_null("memory allocation error");
	}
	return pa;
}

/** \fn size_type find(parray_list pa, value_type val, int (*cmp)(const value_type v1, const value_type v2))
 *
 * Find the index where the element having a value equal to
 * the given value.
 * \param pa The array list where to search.
 * \param val The given value to be searched.
 * \param cmp The compare function provided by caller.
 *        If a NULL pointer is provided, the equal sign
 *        will be used. Otherwise the provided compare
 *        function will be used.
 * \return Return -1 on failure of search, non-negative
 *         integer otherwise.
 */
size_type 
al_find(parray_list pa, value_type val,
    int (*cmp)(const value_type v1, const value_type v2)) {
	if (pa == NULL)
	    return ERROR;
	/** 
	 * If no compare function is provided,
	 * the simple equal sign is used.
	 */
	if (cmp == NULL) {
	    for (size_type i = 0; i < pa->size; i++)
		    if (*(pa->items + i) == val)
			    return i;
	} else {
	    /**
		 * If a compare function is provided, 
		 * use this function.
		 */
	    for (size_type i = 0; i < pa->size; i++)
		    if (cmp(*(pa->items + i), val) == 0)
			    return i;
	}
	// If no element with the given value, -1 is returned
	// to indicate the failure of search.
	return ERROR;
}

/** \fn static int reserve(parray_list pa, size_type new_cap)
 *
 * Resie a given array list such that it can
 * accommodate a given number of values.
 * \param pa The pointer to an array list.
 * \param new_cap The new capacity of this array list.
 * \return Return -1 n memory allocation error,
 *         0 otherwise.
 */
static int 
reserve(parray_list pa, size_type new_cap) {
    value_type *pi;

	if (pa == NULL || pa->capacity >= new_cap)
	    return OK;
	if ((pi = (value_type *) malloc(sizeof(value_type)
	    * new_cap)) == NULL)
		error_negative("memory allocation error");
	for (size_type i = 0; i < pa->size; i++)
	    *(pi + i) = *(pa->items + i);
	free(pa->items);
	pa->items = pi;
	pa->capacity = new_cap;
	return OK;
}

/** \fn int move_back(parray_list pa, size_type from, size_type n_back)
 *
 * Move the elements after an index (provided by the caller)
 * n positions back.
 * \param pa The array list pointer.
 * \param from The elements after this index will be 
 *        moved backward.
 * \param n_back This parameter points out how many positions
 *               these elements will be moved back.
 * \return Return -1 on failure, 0 on success.
 */
static int 
move_back(parray_list pa, size_type from, size_type n_back) {
    if (pa->capacity <= from + n_back)
        return ERROR;
    for (size_type i = pa->size; i > from; i--)
        *(pa->items + i - 1 + n_back) = *(pa->items + i - 1);
    return OK;
}

/** \fn static int insert(parray_list pa, size_type index, value_type val)
 *
 * Insert a new value before a given index.
 * \param pa The array list.
 * \param index The index before which a new value will be inserted.
 * \param val The new value.
 * \return Returns -1 on error, 0 on success.
 */
static int 
insert(parray_list pa, size_type index, value_type val) {
    if (index <= pa->size) {
        if (pa->size + 1 > pa->capacity)
            if (reserve(pa, pa->capacity * 2) < 0)
                error_dump("array list memory allocation error.");
        move_back(pa, index, 1);
        *(pa->items + index) = val;
        pa->size++;
        return OK;
    }
    return ERROR;
}

/** \fn int insert_head(parray_list pa, value_type val)
 *
 * Insert a new value to the head of this array list.
 * \param pa The array list.
 * \param val The new value.
 * \return Return -1 on error, 0 on success.
 */
int 
al_insert_head(parray_list pa, value_type val) {
    return insert(pa, 0, val);
}

/** \fn int insert_tail(parray_list pa, value_type val)
 *
 * Insert a new value into the end of this list.
 * \param pa The list where the new value to be inserted.
 * \param val The new value.
 * \return Return -1 on error, 0 on success.
 */
int 
al_insert_tail(parray_list pa, value_type val) {
    return insert(pa, pa->size, val);
}

/** \fn int insert_before(parray_list pa, value_type val, value_type new)
 *
 * Insert a new value before a given value.
 * \param pa The array list where the new value to be inserted.
 * \param val The value before which a new value is to be inserted.
 * \param new The new value to be inserted.
 * \return Return -1 on error, 0 otherwise.
 */
int 
al_insert_before(parray_list pa, value_type val, value_type new,
    int (*cmp)(const value_type v1, const value_type v2)) {
    size_type index;
    if ((index = al_find(pa, val, cmp)) < 0)
        return ERROR;
    return insert(pa, index, new);
}

/** \fn int move_forward(parray_list pa, size_type index, size_type n)
 *
 * Move the elements after a given index n-position forward.
 * Be aware of that this function does not decrease the size 
 * of given array list. It is up to the caller of this function
 * to maintain the consistence of the size of this array list.
 * \param pa An array list.
 * \param index The given index.
 * \param n Denoting how many positions to be move forward.
 * \return Return -1 on error, 0 otherwise.
 */
static int 
move_forward(parray_list pa, size_type index, size_type n) {
    if (index < 0 || index >= pa->size || n < 0)
        return ERROR;
    if (index - n < 0)
        return ERROR;
    for (size_type i = index; i < pa->size; i++)
        *(pa->items + i - n) = *(pa->items + i);
    return OK;
}

/** \fn int delete(parray_list pa, size_type index)
 *
 * Delete an element at the given index from an 
 * array list.
 * \param pa An array list.
 * \param index The given index.
 * \return Return -1 on deletion failure, 0 otherwise.
 */
int
al_delete(parray_list pa, size_type index) {
    if (index >= pa->size || index < 0)
        return ERROR;
    if (index != pa->size - 1)
        if (move_forward(pa, index + 1, 1) < 0)
            return ERROR;
    pa->size--;
    return OK;
}

/** \fn int delete_value(parray_list pa, value_type val)
 *
 * Delete a given value from an array list.
 * \param pa An array list.
 * \param val The value to be deleted.
 * \return Return -1 on deletion failure, 0 otherwise.
 */
int
al_delete_value(parray_list pa, value_type val,
    int (*cmp)(const value_type v1, const value_type v2)) {
    size_type index;
    if ((index = al_find(pa, val, cmp)) < 0)
        return ERROR;
    return al_delete(pa, index);
}

/** \fn int is_empty(parray_list pa)
 *
 * Check whether the given array list is empty.
 * \param pa The array list.
 * \return Return 0 if not empty, 1 otherwise.
 */
int
al_is_empty(parray_list pa) {
    return pa->size == 0;
}

/** \fn void clear(parray_list pa)
 * 
 * Clear the elements in this array list.
 * \param pa The array list.
 */
void 
al_clear(parray_list pa) {
    pa->size = 0;
}

/** void free_array_list(parray_list pa)
 *
 * Free the memory occuried by given array list.
 * \param pa The array list.
 */
void
free_array_list(parray_list pa) {
    if (pa == NULL)
        return;
    if (pa->items != NULL)
        free(pa->items);
    free(pa);
}

/** \fn size_type size_of_array_list(parray_list pa)
 * \brief Return the current size of this array list.
 */
size_type size_of_array_list(parray_list pa) {
    return pa->size;
}
