/** @file avl_tree.c
 *
 * Function definitions for AVL tree.
 */

#include "avl_tree.h"

/** @fn pavl_node create_avl_node(value_type key)
 * \brief Create a node for AVL tree with given key value.
 */
pavl_node
create_avl_node(value_type key) {
    pavl_node node;

	if ((node = (pavl_node) malloc(sizeof(avl_node)))
	     == NULL)
        error_null("memory error: create_avl_node()");
	
	node->key = key;
	node->left =  node->right = NULL;
	node->height = -1;

	return node;
}

/** @fn pval_tree create_avl_tree(void)
 * 
 * Create an empty AVL tree.
 */
pavl_tree
create_avl_tree(void) {
    pavl_tree tree;

	if ((tree = (pavl_tree)malloc(sizeof(avl_tree)))
	     == NULL)
	    error_null("memory error: create_avl_tree()");

	tree->root = NULL;
	tree->size = 0;

	return tree;
}

/** @fn static size_type height(pavl_node subtree)
 *
 * Return the height of a subtree.
 * @return Returns -1 on error, a non-negative integer otherwise.
 */
static size_type
height(pavl_node subtree) {
    if (subtree == NULL)
	    return -1;
	return subtree->height;
}

/** @fn static size_type max(size_type val1, size_type val2)
 *
 * Return the maximal one between two integers.
 */
static size_type
max(size_type val1, size_type val2) {
    return val1 >= val2 ? val1 : val2;
}

/** @fn static int update_height(pavl_node subtree)
 *
 * Update the height of a subtree.
 */
static int
update_height(pavl_node subtree) {
    if (subtree == NULL)
	    return ERROR;
	subtree->height = max(height(subtree->left),
	                      height(subtree->right)) + 1;
	return OK;
}

/** @fn static pavl_node single_right_rotation(pavl_node subtree)
 *
 * Perform a right-to-left rotation on a subtree.
 * @param subtree An AVL subtree on which the rotation will perform.
 * @return Returns the new root of this subtree after rotation.
 */
static pavl_node
single_right_rotation(pavl_node subtree) {
    pavl_node new_sub;

    if (subtree == NULL || subtree->right == NULL)
	    return NULL;

    new_sub = subtree->right;
	subtree->right = new_sub->left;
	new_sub->left = subtree;

    update_height(subtree);
	update_height(new_sub);

	return new_sub;
}

/** @fn static pavl_node single_left_rotation(pavl_node subtree)
 *
 * Perform a left-to-right rotation on a subtree.
 * @param subtree An AVL subtree on which the rotation will perform.
 * @return Returns the new root of this subtree after rotation.
 */
static pavl_node
single_left_rotation(pavl_node subtree) {
    pavl_node new_sub;
	if (subtree == NULL || subtree->left == NULL)
	    return NULL;
	
	new_sub = subtree->left;
	subtree->left = new_sub->right;
	new_sub->right = subtree;

	update_height(subtree);
	update_height(new_sub);

	return new_sub;
}

/** @fn static pavl_node double_right_rotation(pavl_node subtree)
 *
 * Perform a double rotation, which firstly starts a left-to-right
 * rotation then a right-to-left one, on a subtree.
 * @param subtree An AVL subtree, on which the rotation will perform.
 * @return Returns the new root of this subtree after rotation.
 */
static pavl_node
double_right_rotation(pavl_node subtree) {
    if (subtree == NULL || subtree->right == NULL)
	    return NULL;
	
	subtree->right = single_left_rotation(subtree->right);
	return single_right_rotation(subtree);
}

/** static pavl_node double_left_rotation(pavl_node subtree)
 *
 * Perform a double rotation, which firstly starts a right-to-left
 * rotation then a left-to-right one, on a subtree.
 * @param subtree An AVL subtree, on which the rotation will perform.
 * @return Returns the new root of this subtree after rotation.
 */
static pavl_node
double_left_rotation(pavl_node subtree) {
    if (subtree == NULL || subtree->left == NULL)
	    return NULL;
	
	subtree->left = single_right_rotation(subtree->left);
	return single_left_rotation(subtree);
}

/** @fn static pavl_node recur_insert(pavl_node subtree, value_type key, CMP_FUNC cmp)
 *
 * Recursively insert a key into an AVL subtree.
 * @param subtree An AVL subtree.
 * @param key Given key.
 * @param cmp Function used to compare two values.
 * @return Returns current subtree.
 */
static pavl_node
recur_insert(pavl_node subtree, value_type key, CMP_FUNC cmp) {
    if (subtree == NULL) {
	    if ((subtree = create_avl_node(key)) == NULL)
		    return NULL;
		subtree->height = 0;
	} else if (cmp == NULL) {
	    if (subtree->key < key) {
		    subtree->right = recur_insert(subtree->right, key, cmp);
			if (height(subtree->right) - 
			    height(subtree->left) >= 2)
			    if (subtree->right->key < key)
				    subtree = single_right_rotation(subtree);
				else
				    subtree = double_right_rotation(subtree);
		} else {
		    subtree->left = recur_insert(subtree->left, key, cmp);
			if (height(subtree->left) - 
			    height(subtree->right) >= 2)
			    if (subtree->left->key >= key)
				    subtree = single_left_rotation(subtree);
				else
				    subtree = double_left_rotation(subtree);
		}
	} else {
	    if (cmp(subtree->key, key) < 0) {
		    subtree->right = recur_insert(subtree->right, key, cmp);
			if (height(subtree->right) - 
			    height(subtree->left) >= 2)
			    if (cmp(subtree->right->key, key) < 0)
				    subtree = single_right_rotation(subtree);
				else
				    subtree = double_right_rotation(subtree);
		} else {
		    subtree->left = recur_insert(subtree->left, key, cmp);
			if (height(subtree->left) - 
			    height(subtree->right) >= 2)
			    if (cmp(subtree->left->key, key) >= 0)
				    subtree = single_left_rotation(subtree);
				else
				    subtree = double_left_rotation(subtree);
		}
	}

    update_height(subtree);
    
	return subtree;
}

/** @fn int avl_recur_insert(pavl_tree tree, value_type key, CMP_FUNC cmp)
 *
 * Insert a new with given key to an AVL tree.
 * @param tree An AVL tree.
 * @param key Given key.
 * @param cmp Function used to compare two values.
 * @return Returns -1 on error, 0 otherwise.
 */
int
avl_recur_insert(pavl_tree tree, value_type key, CMP_FUNC cmp) {
    if (tree == NULL)
	    return ERROR;
	tree->root = recur_insert(tree->root, key, cmp);
	return OK;
}
