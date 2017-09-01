#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node node;

typedef struct node {
	char item;
	node *next;
} node;

typedef struct list list;

struct list {
	node *root;
	int size;
};

list *create();
void add(list *, char);
node *search(list *, char);
void remove_node(list *, char);
//void change
void dump(list *);
void destroy(list **);

#endif
