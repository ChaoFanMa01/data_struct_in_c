/** \file avl_tree.h
 *
 * Type definitions and function declartions
 * for AVL tree.
 */

#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <stdlib.h>
#include <sys/types.h>
#include "../header.h"

typedef int      value_type;
typedef ssize_t   size_type;

typedef struct _AVL_NODE avl_node;
typedef struct _AVL_TREE avl_tree;

typedef avl_node    *pavl_node;
typedef avl_tree    *pavl_tree;

typedef int (*CMP_FUNC)(value_type, value_type);
typedef void (*PRINT_FUNC)(value_type);

struct _AVL_NODE {
    value_type key;    /**< The key value in this node */
    pavl_node  left;   /**< Pointer to its left child */
	pavl_node  right;  /**< Pointer to its right child */
	size_type  height; /**< The height of this node */
};

struct _AVL_TREE {
    pavl_node    root; /**< The root of a AVL tree */
	size_type    size; /**< The size of this tree */
};

pavl_node create_avl_node(value_type key);
pavl_tree create_avl_tree(void);
value_type avl_min(pavl_tree tree);
value_type avl_max(pavl_tree tree);
int avl_recur_insert(pavl_tree tree, value_type key, CMP_FUNC cmp);
int avl_recur_remove(pavl_tree tree, value_type key, CMP_FUNC cmp);
void avl_recur_inorder_walk(pavl_tree tree, PRINT_FUNC print);

#endif
