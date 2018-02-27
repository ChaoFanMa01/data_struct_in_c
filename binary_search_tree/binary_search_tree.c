/** \file binary_search_tree.c
 *
 * Function definitions for binary search tree.
 */

#include "binary_search_tree.h"

/** \fn pbst_node create_bst_node(value_type key)
 * 
 * Create a binary search tree node.
 */
pbst_node 
create_bst_node(value_type key) {
    pbst_node node;

	if ((node = (pbst_node) malloc(sizeof(struct bst_node))
	     == NULL))
	    error_null("memory error: create_bst_node()");
	
	node->key = key;
	node->left = NULL;
	node->right = NULL;

	return node;
}

/** \fn pbst create_bst(void)
 * \brief Create a binary search tree.
 */
pbst
create_bst(void) {
    pbst tree;

	if ((tree = (pbst) malloc(sizeof(struct bst))) == NULL)
	    error_null("memory error: create_bst()");

	root->root = NULL;

	return root;
}

/** \fn pbst_node bst_recur_search_node(pbst tree, value_type key, int (*cmp)(value_type, value_type))
 *
 * Recursively search a node containing given value from a 
 * binary search tree.
 * \param tree A binary search tree.
 * \param key Given value.
 * \param cmp Function used to compare two values.
 * \return Returns null pointer when misfound, a non-null
 *                 pointer otherwise.
 */
pbst_node
bst_recur_search_node(pbst tree, value_type key,
                int (*cmp)(value_type, value_type)) {
	if (tree == NULL)
	    return NULL;
    return bst_subtree_recur_search_node(tree->root, key cmp);
}

/** \fn pbst_node bst_subtree_recur_search_node(pbst_node subtree, value_type key, int (*cmp)(value_type, value_type))
 *
 * Recursively search a node containing given value from a 
 * binary search subtree.
 * \param subtree A binary search subtree.
 * \param key Given value.
 * \param Function used to compare two values.
 * \return Returns null pointer when misfound, a non-null 
 *         pointer otherwise.
 */
pbst_node
bst_subtree_recur_search_node(pbst_node subtree, value_type key,
            int (*cmp)(value_type, value_type)) {
    if (subtree == NULL)
	    return NULL;
	if (cmp == NULL) {
	    if (subtree->key == key)
		    return subtree;
		else if (subtree->key < key)
		    return bst_subtree_recur_search_node(subtree->right, key, cmp);
		else
		    return bst_subtree_recur_search_node(subtree->left, key, cmp);
	} else {
	    if (cmp(key, subtree->key) == 0)
		    return subtree;
		else if (cmp(subtree->key, key) < 0)
		    return bst_subtree_recur_search_node(subtree->right, key, cmp);
		else
		    return bst_subtree_recur_search_node(subtree->left, key, cmp);
	}
}

/** \fn pbst_node bst_iter_search_node(pbst tree, value_type key, int (*cmp)(value_type, value_type))
 *
 * Iteratively search a node containing given value from 
 * a binary search tree.
 * \param tree A binary search tree.
 * \param key Given value.
 * \param cmp Function used to compare two values.
 * \return Returns null pointer when misfound, a non-null
 *                 pointer otherwise.
 */
pbst_node
bst_iter_search_node(pbst tree, value_type key,
                     int (*cmp)(value_type, value_type)) {
    return bst_subtree_iter_search_node(tree->root, key, cmp);
}

/** \fn pbst_node bst_subtree_iter_search_node(pbst_node subtree, value_type key, int (*cmp)(value_type, value_type))
 *
 * Iteratively search a node containing given value from 
 * a binary search subtree.
 * \param subtree A binary search subtree.
 * \param key Given value.
 * \param cmp Function used to compare two values.
 * \return Returns null pointer when misfound, non-pointer
 *                 otherwise.
 */
pbst_node
bst_subtree_iter_search_node(pbst_node subtree, value_type key,
            int (*cmp)(value_type, value_type)) {
    if (subtree == NULL)
	    return NULL;
	while (subtree != NULL)
	    if (cmp == NULL) {
		    if (subtree->key == key)
			    return subtree;
			else if (subtree->key < key)
			    subtree = subtree->right;
			else
			    subtree = subtree->left;
		} else {
		    if (cmp(subtree->key, key) == 0)
			    return subtree;
			else if (cmp(subtree->key, key) < 0)
			    subtree = subtree->right;
			else
			    subtree = subtree->left;
		}
	
	return NULL;
}

/** \fn value_type *bst_min(pbst tree)
 * \brief Find the minimal value from a binary search tree.
 */
value_type *
bst_min(pbst tree) {
	if (tree == NULL || tree->root == NULL)
	    return NULL;
	
	for (pbst_node temp = tree->root; ; temp = temp->left)
	    if (temp->left == NULL)
		    return &temp->key;
}

/** \fn pbst_node bst_min_node(pbst tree)
 * \brief Find the node with minimal key value from a
 *        binary search tree.
 */
pbst_node
bst_min_node(pbst tree) {
    if (tree == NULL || tree->root == NULL)
	    return NULL;
	
	for (pbst_node temp = tree->root; ; temp = temp->left)
	    if (temp->left == NULL)
		    return temp;
}

/** \fn value_type *bst_max(pbst tree)
 * \brief Find the maximal value from a binary search tree.
 */
value_type *
bst_max(pbst tree) {
	if (tree == NULL || tree->root == NULL)
	    return NULL;
	
	for (pbst_node temp = tree->root; ; temp = temp->right)
	    if (temp->right == NULL)
		    return &temp->key;
}

/** pbst_node bst_max_node(pbst tree)
 * \brief Find the node with the maximal key value from a 
 *        binary search tree.
 */
pbst_node
bst_max_node(pbst tree) {
	if (tree == NULL || tree->root == NULL)
	    return NULL;
	
	for (pbst_node temp = tree->root; ; temp = temp->right)
	    if (temp->right == NULL)
		    return temp;
}

/** \fn void print_depth(size_type depth)
 * \brief Print given number of space.
 */
void
print_depth(size_type depth) {
    for (size_type i = 0; i < depth; i++)
	    printf(" ");
}

/** \fn void bst_recur_inorder_walk(pbst tree, void (*print)(value_type))
 * \brief Recursive inorder walk for a binary search tree.
 *
 * \param tree A binary search tree.
 * \param print Function used to print the key value of a node.
 */
void
bst_recur_inorder_walk(pbst tree,
                       void (*print)(value_type)) {
    bst_recur_subtree_inorder_walk(tree->root, 0, print);
}

/** \fn void bst_recur_subtree_inorder_walk(pbst_node subtree, size_type depth, void (*print)(value_type))
 * \brief Recursive inorder walk for a binary search subtree.
 *
 * \param subtree A binary search subtree.
 * \param depth The depth of this subtree.
 * \param print Function used to print the key value of a node.
 */
void
bst_recur_subtree_inorder_walk(pbst_node subtree, size_type depth,
                               void (*print)(value_type)) {
    if (subtree == NULL)
	    return;
	bst_recur_subtree_inorder_walk(subtree->left, depth++, print);
	print_depth(depth);
    print(subtree->key);
	bst_recur_subtree_inorder_walk(subtree->right, depth++, print);
}

/** \fn void bst_recur_preorder_walk(pbst tree, void (*print)(value_type))
 * \brief Recursive preorder walk for a binary search tree.
 *
 * \param tree A binary search tree.
 * \param print Function used to print the key value of a node.
 */
void
bst_recur_preorder_walk(pbst tree,
                       void (*print)(value_type)) {
    bst_recur_subtree_preorder_walk(tree->root, 0, print);
}


/** \fn void bst_recur_subtree_preorder_walk(pbst_node subtree, size_type depth, void (*print)(value_type))
 * \brief Recursive preorder walk for a binary search subtree.
 *
 * \param subtree A binary search subtree.
 * \param depth The depth of this subtree.
 * \param print Function used to print the key value of a node.
 */
void
bst_recur_subtree_preorder_walk(pbst_node subtree, size_type depth,
                               void (*print)(value_type)) {
    if (subtree == NULL)
	    return;
	print_depth(depth);
    print(subtree->key);
	bst_recur_subtree_preorder_walk(subtree->left, depth++, print);
	bst_recur_subtree_preorder_walk(subtree->right, depth++, print);
}

/** \fn void bst_recur_postorder_walk(pbst tree, void (*print)(value_type))
 * \brief Recursive postorder walk for a binary search tree.
 *
 * \param tree A binary search tree.
 * \param print Function used to print the key value of a node.
 */
void
bst_recur_postorder_walk(pbst tree,
                       void (*print)(value_type)) {
    bst_recur_subtree_postorder_walk(tree->root, 0, print);
}

/** \fn void bst_recur_subtree_postorder_walk(pbst_node subtree, size_type depth, void (*print)(value_type))
 * \brief Recursive postorder walk for a binary search subtree.
 *
 * \param subtree A binary search subtree.
 * \param depth The depth of this subtree.
 * \param print Function used to print the key value of a node.
 */
void
bst_recur_subtree_postorder_walk(pbst_node subtree, size_type depth,
                               void (*print)(value_type)) {
    if (subtree == NULL)
	    return;
	bst_recur_subtree_postorder_walk(subtree->left, depth++, print);
	bst_recur_subtree_postorder_walk(subtree->right, depth++, print);
	print_depth(depth);
    print(subtree->key);
}

/** \fn int bst_insert(pbst tree, pbst_node node, int (*cmp)(value_type, value_type))
 *
 * Insert a node to a binary search tree.
 * \param tree A binary search tree.
 * \param node A node.
 * \param cmp Function used to compare two values.
 * \return Return -1 on error, 0 otherwise.
 */
int
bst_insert(pbst tree, pbst_node node,
           int (*cmp)(value_type, value_type)) {
    pbst_node cur, hld = NULL;

    if (tree == NULL || node == NULL)
	    return ERROR;

    cur = tree->root;
	while (cur != NULL) {
	    temp = cur;
		if (cmp == NULL) {
		    if (node->key > cur->key)
			    cur = cur->right;
			else
			    cur = cur->left;
		} else {
		    if (cmp(node->key, cur->key) > 0)
			    cur = cur->right;
			else
			    cur = cur->left;
		}
	}

    if (temp == NULL) {
	    tree->root = node;
	} else if (node->key > temp->key) {
	    temp->right = node;
	} else {
	    temp->left = node;
	}
	return OK;
}

/** \fn pbst_node bst_find_parent(pbst tree, pbst_node node, int (*cmp)(value_type, value_type))
 *
 * Find the parent of given node from a binary search tree.
 * \param tree A binary search tree.
 * \param node Given node whose parent to be searched.
 * \param cmp Function used to compare two values.
 * \return Rerturns null pointer when not found, a non-null
 *                  pointer otherwise.
 */
pbst_node
bst_find_parent(pbst tree, pbst_node node,
                int (*cmp)(value_type, value_type)) {
    if (tree == NULL || tree->root == NULL)
	    return NULL;
	
	if (cmp == NULL) {
	    for (pbst_node parent = tree->root; parent != NULL; )
		    if (parent->left == node || parent->right == node) {
			    return parent;
			} else if (parent->key < node->key) {
			    parent = parent->right;
			} else {
			    parent = parent->left;
			}
	} else {
	    for (pbst_node parent = tree->root; parent != NULL; )
		    if (parent->left == node || parent->right == node) {
			    return parent;
			} else if (cmp(parent->key, node->key) < 0) {
			    parent = parent->right;
			} else {
			    parent = parent->left;
			}
	}
	return NULL;
}

/** \fn int bst_transplant(pbst tree, pbst_node del, pbst_node sub)
 *
 * Use a node to substitute another in a binary search tree.
 * \param tree A binary search tree.
 * \param del The node to be substituted.
 * \param sub The node used to subtitute another node.
 * \return Returns -1 on error, 0 otherwise.
 */
int
bst_transplant(pbst tree, pbst_node del, pbst_node sub,
               int (*cmp)(value_type, value_type)) {
    pbst_node parent;
    if (tree == NULL || tree->root == NULL)
	    return ERROR;
	if ((parent = bst_find_parent(tree, del, cmp)) == NULL) {
	    tree->root = sub;
	} else if (parent->right == del) {
	    parent->right = sub;
	} else {
	    parent->left = sub;
	}
	return OK;
}

/** int bst_delete(pbst tree, value_type key, int (*cmp)(value_type, value_type))
 *
 * Delete given key from a binary search tree.
 * \param tree A binary search tree.
 * \param key Given key value.
 * \param cmp Function used to compare two values.
 * \return Returns -1 on error, 0 otherwise.
 */
int
bst_delete(pbst tree, value_type key, 
           int (*cmp)(value_type, value_type)) {
    pbst_node node, min;
	if (tree == NULL || tree->root == NULL)
	    return ERROR;
	
	// Not found such value from given BST.
	if ((node = bst_iter_search_node(tree, key, cmp)) == NULL) {
	    return ERROR;
	  // Case 1.
	} else if (node->left == NULL) {
	    bst_transplant(tree, node, node->right, cmp);
	  // Case 2.
	} else if (node->right == NULL) {
	    bst_transplant(tree, node, node->left, cmp);
	  // Case 3.
	} else if (node->right->left == NULL) {
	    node->right->left = node->left;
	    bst_transplant(tree, node, node->right, cmp);
	  // Case 4.
	} else {
	    min = bst_min_node(tree);
		bst_transplant(tree, min, min->right, cmp);
		min->right = node->right;
		min->left = node->left;
		bst_transplant(tree, node, min, cmp);
	}
	return OK;
}
