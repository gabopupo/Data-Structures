#ifndef STACK_H
#define STACK_H

typedef struct node node;

struct node {
	node *prev;
	int item;
};

typedef struct stack stack;

struct stack {
	node *top;
	int size;
};

stack *create();
void push(stack *, int);
int pop(stack *);
int peek(stack *);
int empty(stack *);
void print(stack *);
void destroy(stack **);

#endif
