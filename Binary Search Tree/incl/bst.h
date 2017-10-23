#ifndef BST_H
#define BST_H

typedef struct node node;

struct node {
	int key;
	node *left, *right;
};

typedef enum b_type b_type;

enum b_type {
	PREORDER,
	INORDER,
	POSTORDER
};

void add(node **, int);
void browse(node *, b_type);
node *search(node *, int);
void delete(node **, int);

#endif
