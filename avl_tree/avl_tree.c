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

/** @fn static value_type subtree_min(pavl_node subtree)
 *
 * Return the minimal key of an AVL subtree.
 */
static value_type
subtree_min(pavl_node subtree) {
    while (subtree->left != NULL)
	    subtree = subtree->left;
	return subtree->key;
}

/** @fn value_type avl_min(pavl_tree tree)
 *
 * Return the minimal key of an AVL tree.
 */
value_type
avl_min(pavl_tree tree) {
    return subtree_min(tree->root);
}

/** @fn static value_type subtree_max(pavl_node subtree)
 *
 * Return the maximal key of an AVL subtree.
 */
static value_type
subtree_max(pavl_node subtree) {
    while (subtree->right != NULL)
	    subtree = subtree->right;
	return subtree->key;
}

/** @fn value_type avl_max(pavl_tree tree)
 *
 * Return the minimal key of an AVL tree.
 */
value_type
avl_max(pavl_tree tree) {
    return subtree_max(tree->root);
}

/** @fn static pavl_node recur_remove(pavl_node subtree, value_type key, CMP_FUNC cmp)
 *
 * Recursively remove a given from an AVL subtree.
 * @param subtree An AVL subtree.
 * @param key Given key.
 * @param cmp Function used to compare two values.
 * @return Returns new root of this subtree after removal.
 */
static pavl_node 
recur_remove(pavl_node subtree, value_type key, CMP_FUNC cmp) {
    if (subtree == NULL)
	    return NULL;
	
	if (cmp == NULL) {
        if (subtree->key < key) {
		    subtree->right = recur_remove(subtree->right, key, cmp);
			if (height(subtree->left) - height(subtree->right)
			    >= 2)
			    if (height(subtree->left) > height(subtree->right))
				    subtree = single_left_rotation(subtree);
				else
				    subtree = double_left_rotation(subtree);
		} else if (subtree->key > key) {
		    subtree->left = recur_remove(subtree->left, key, cmp);
			if (height(subtree->right) - height(subtree->left)
			    >= 2)
			    if (height(subtree->right) > height(subtree->left))
				    subtree = single_right_rotation(subtree);
				else
				    subtree = double_right_rotation(subtree);
		} else if (subtree->left != NULL && subtree->right != NULL) {
		    subtree->key = subtree_min(subtree->right);
			subtree->right = recur_remove(subtree->right, 
			                              subtree->key, cmp);
			if (height(subtree->left) - height(subtree->right)
			    >= 2)
			    if (height(subtree->left) > height(subtree->right))
				    subtree = single_left_rotation(subtree);
				else
				    subtree = double_left_rotation(subtree);
		} else {
		    pavl_node temp = subtree;
			subtree = subtree->left != NULL ? subtree->left :
			                                  subtree->right;
			free(temp);
		}
	} else {
        if (cmp(subtree->key, key) < 0) {
		    subtree->right = recur_remove(subtree->right, key, cmp);
			if (height(subtree->left) - height(subtree->right)
			    >= 2)
			    if (height(subtree->left) > height(subtree->right))
				    subtree = single_left_rotation(subtree);
				else
				    subtree = double_left_rotation(subtree);
		} else if (cmp(subtree->key, key) > 0) {
		    subtree->left = recur_remove(subtree->left, key, cmp);
			if (height(subtree->right) - height(subtree->left)
			    >= 2)
			    if (height(subtree->right) > height(subtree->left))
				    subtree = single_right_rotation(subtree);
				else
				    subtree = double_right_rotation(subtree);
		} else if (subtree->left != NULL && subtree->right != NULL) {
		    subtree->key = subtree_min(subtree->right);
			subtree->right = recur_remove(subtree->right, 
			                              subtree->key, cmp);
			if (height(subtree->left) - height(subtree->right)
			    >= 2)
			    if (height(subtree->left) > height(subtree->right))
				    subtree = single_left_rotation(subtree);
				else
				    subtree = double_left_rotation(subtree);
		} else {
		    pavl_node temp = subtree;
			subtree = subtree->left != NULL ? subtree->left :
			                                  subtree->right;
			free(temp);
		}
	}

	update_height(subtree);
	
	return subtree;
}

/** @fn int avl_recur_remove(pavl_tree tree, value_type key, CMP_FUNC cmp)
 *
 * Recursively remove a given key from an AVL tree.
 * @fn tree An AVL tree.
 * @fn key Given key.
 * @fn cmp Function used to compare two values.
 */
int 
avl_recur_remove(pavl_tree tree, value_type key,
                 CMP_FUNC cmp) {
    if (tree == NULL || tree->root == NULL)
	    return ERROR;
	
	tree->root = recur_remove(tree->root, key, cmp);
	return OK;
}

/** @fn static void print_depth(size_type depth)
 *
 * Print given number of blank space.
 */
static void
print_depth(size_type depth, size_type height) {
    printf("%2d|%2d|", depth, height);
    for (size_type i = 0; i < depth; i++)
	    printf("-");
}

/** @fn static void recur_inorder_walk(pavl_node subtree, size_type depth, PRINT_FUNC print)
 *
 * Recursively traverse an AVL subtree in an inorder manner.
 * @param subtree An AVL subtree.
 * @param depth The depth of this subtree.
 * @param print Function used to print key.
 */
static void
recur_inorder_walk(pavl_node subtree, size_type depth, 
                   PRINT_FUNC print) {
    if (subtree == NULL || print == NULL)
	    return;
	recur_inorder_walk(subtree->left, depth + 1, print);
	print_depth(depth, subtree->height);
	print(subtree->key);
	recur_inorder_walk(subtree->right, depth + 1, print);
}

/** @fn void avl_recur_inorder_walk(pavl_tree tree, PRINT_FUNC print)
 *
 * Recursively traverse an AVL tree in an inorder manner.
 * @param tree An AVL tree.
 * @param print Function used to print key.
 */
void
avl_recur_inorder_walk(pavl_tree tree, PRINT_FUNC print) {
    if (tree == NULL)
	    return;
    recur_inorder_walk(tree->root, 0, print);
}
