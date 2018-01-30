/** \file array_list.h
 *
 * Type definitions, function declarations for
 * list implemented based on array.
 */

#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include <sys/types.h>

/** \typedef typedef int value_type
 * \brief Type for the data stored in an array list.
 */
typedef int       value_type;
/** \typedef size_t size_type
 * \brief Type denoting the size of an array.
 */
typedef size_t    size_type;

/** \typedef array_list
 *
 * Type for the structure implementing the 
 * array list.
 */
typedef struct {
    size_type    capacity; /**< The maximum number of
	                        * elements that can be hold
							* in this array list.
							*/
	size_type    size;     /**< The current number of
	                        * elements hold in this
							* array list.
							*/
	value_type  *items;    /**< The array where actually
	                        * storing the elements.
							*/
} array_list;

/** \typedef typedef array_list *parray_list
 * \brief Type for the pointer pointing to
 * an array list.
 */
typedef array_list *parray_list;

/** \var static const size_t INIT_CAP
 * \brief The default capacity of an array
 * list.
 */
static const size_t INIT_CAP = 10;

parray_list create_array_list(void);
parray_list create_array_list_n(size_type n);
size_type find(parray_list pa, value_type val, int (*cmp)(const value_type v1, const value_type v2));
static int reserve(parray_list pa, size_type new_cap);
static int move_back(parray_list pa, size_type from, size_type n_back);
static int insert(parray_list pa, size_type index, value_type val);
int insert_head(parray_list pa, value_type val);
int insert_tail(parray_list pa, value_type val);
int insert_before(parray_list pa, value_type val, value_type new, int (*cmp)(const value_type v1, const value_type v2));
static int move_forward(parray_list pa, size_type index, size_type n);
int delete(parray_list pa, size_type index);
int delete_value(parray_list pa, value_type val, int (*cmp)(const value_type v1, const value_type v2));
int is_empty(parray_list pa);
void clear(parray_list pa);
void free_array_list(parray_list pa);
size_type size_of_array_list(parray_list pa);

#endif
