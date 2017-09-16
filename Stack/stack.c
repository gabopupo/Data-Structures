#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "stack.h"

stack *create() {
	stack *new = (stack *) malloc (sizeof(stack));
	
	if (new != NULL) {
		new->top = NULL;
		new->size = 0;
	}

	return new;
}

void push(stack *st, int item) {
	node *psh = (node *) malloc (sizeof(node));

	if (psh != NULL) {
		psh->prev = st->top;
		st->top = psh;

		psh->next = NULL;
		psh->item = item;

		st->size++;
	}
}

int pop(stack *st) {
	int pop;

	if (!empty(st)) {
		pop = st->top->item;
		node *rem = st->top;
		st->top = st->top->prev;
		
		free(rem);
		st->size--;

		return pop;
	}

	return INT_MIN;
}

int peek(stack *st) {
	return st->top->item;
}

int empty(stack *st) {
	return (st->size == 0);
}

void print(stack *st) {
	node *nav = st->top;

	if (empty(st)) {
		printf("The stack is empty.\n");
		return;
	}

	printf("top: ");
	while (nav != NULL) {
		printf("%d ", nav->item);
		nav = nav->prev;
	}
	printf("\n");
}

void destroy(stack **st) {
	while (!empty(*st)) pop(*st);
	free(*st);
	*st = NULL;
}
