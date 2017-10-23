#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

node *create_node(int k) {
	node *r = (node *) malloc (sizeof(node));
	if (r != NULL) {
		r->left = NULL; r->right = NULL;
		r->key = k;
	}
	return r;
}

// insertion on a binary search tree must follow two rules:
// * for each root of a tree, all nodes of smaller keys must be on the left subtree.
// on the other hand, all nodes of bigger keys must be on the right subtree.
// * no nodes of repeated keys on any subtree.
void add(node **n, int k) {
	while (*n != NULL) {
		if (k < (*n)->key) n = &(*n)->left;
		else if (k > (*n)->key) n = &(*n)->right;
		else return;
	}

	*n = create_node(k);
}

void visit(node *n) {
	printf("%d\n", n->key);
}

void browse(node *n, b_type t) {
	if (n != NULL) {
		if (t == PREORDER) visit(n);
		browse(n->left, t);
		if (t == INORDER) visit(n);
		browse(n->right, t);
		if (t == POSTORDER) visit(n);
	}
}

node *search(node *n, int k) {
	if (n == NULL)
		return NULL;
	if (n->key == k)
		return n;
	if (n->key > k)
		return search(n->left, k);
	return search(n->right, k);
}

void delete_fix(node *rem, node **chld) {
	if ((*chld)->right != NULL)
		delete_fix(rem, &(*chld)->right);
	else {
		rem->key = (*chld)->key;
		rem = *chld;
		*chld = (*chld)->left;
		free(rem);
	}
}

void delete(node **n, int k) {
	node *rem;
	while (*n != NULL) {
		if (k < (*n)->key) n = &(*n)->left;
		else if (k > (*n)->key) n = &(*n)->right;
		else {
			if ((*n)->left == NULL) { // if there's no left child, swap the right one to parent
				rem = *n;
				*n = (*n)->right;
				free(rem);
			} else if ((*n)->right == NULL) { // if there's no right child, swap the left one to parent
				rem = *n;
				*n = (*n)->left;
				free(rem);
			} else { // there's both the left and the right children
				delete_fix(*n, &(*n)->left);
			}
		}
	}
}
