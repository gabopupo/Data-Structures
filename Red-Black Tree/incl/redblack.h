#ifndef REDBLACK_H
#define REDBLACK_H

#define RED 1
#define BLACK 2

#define PREORDER 6
#define INORDER 7
#define POSTORDER 8

typedef struct node node;

struct node {
	int key, color;
	node *left, *right, *parent;
};

void add(node **, int);
void browse(node *, int);
int predecessor(node *, int);
int successor(node *, int);
int min_value(node *);
int max_value(node *);
void destroy(node **);

#endif
