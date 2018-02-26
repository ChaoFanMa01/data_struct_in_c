/** \file binary_search_tree.h
 *
 * Type definitions, function declarations for 
 * binary search tree.
 */

#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <sys/types.h>
#include <stdlib.h>
#include "../header.h"

/**
 * structure declarations.
 */
struct bst_node;
struct bst;

typedef int     value_type;
typedef size_t  size_type;

typedef struct bst_node      *pbst_node;
typedef struct bst           *pbst;

struct bst_node {
    value_type    key;    /**< The key stored in this node */
	pbst_node     left;   /**< Pointer to its left child */
	pbst_node     right;  /**< Pointer to its right child */
};

struct bst {
    pbst_node root;    /**< The root of this binary search tree */
};

pbst_node create_bst_node(value_type key);
pbst create_bst(void);
pbst_node bst_recur_search_node(pbst tree, value_type key, int (*cmp)(value_type, value_type));
pbst_node bst_subtree_recur_search_node(pbst_node subtree, value_type key, int (*cmp)(value_type, value_type));
pbst_node bst_iter_search_node(pbst tree, value_type key, int (*cmp)(value_type, value_type));
pbst_node bst_subtree_iter_search_node(pbst_node subtree, value_type key, int (*cmp)(value_type, value_type));
value_type *bst_min(pbst tree);
value_type *bst_max(pbst tree);
void print_depth(size_type depth);
void bst_recur_inorder_walk(pbst tree, void (*print)(value_type));
void bst_recur_subtree_inorder_walk(pbst_node subtree, size_type depth, void (*print)(value_type));
void bst_recur_preorder_walk(pbst tree, void (*print)(value_type));
void bst_recur_subtree_preorder_walk(pbst_node subtree, size_type depth, void (*print)(value_type));
void bst_recur_postorder_walk(pbst tree, void (*print)(value_type));
void bst_recur_subtree_postorder_walk(pbst_node subtree, size_type depth, void (*print)(value_type));

#endif
