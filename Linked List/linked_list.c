#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

list *create() {
	list *new = (list *) malloc (sizeof(list));
	if (new != NULL) {
		new->root = NULL;
		new->size = 0;
	}
	return new;
}

node *create_node(char i) {
	node *n = (node *) malloc (sizeof(node));
	if (n != NULL) {
		n->item = i;
		n->next = NULL;
	}
	return n;
}

void add(list *l, char i) {
	node *n = create_node(i);
	node *aux = l->root, *prev;

	if (l->root == NULL) l->root = n;
	else {
		while (aux != NULL) {
			prev = aux;
			aux = aux->next;
		}
	
		prev->next = n;
		n->next = NULL;
	}
	(l->size)++;
}

int search(list *l, char i) {
	int step = 1;
	node *aux = l->root;

	if (l->size == 0) return NULL;

	while (aux != NULL) {
		if (aux->item == i) return step;
		aux = aux->next;
		step++;
	}
	return NULL;
}

void remove_node(list *l, char i) {
	node *aux = l->root;
	node *prev;

	if (l->size == 0) return;
	
	if (l->root->item == i) {
		l->root = aux->next;
		free(aux);
		(l->size)--;
		return;
	}

	while (aux != NULL) {
		if (aux->item == i) {
			prev->next = aux->next;
			free(aux);
			(l->size)--;
			return;
		}

		prev = aux;
		aux = aux->next;
	}
}

void dump(list *l) {
	node *aux = l->root;

	printf("===========\n");
	while (aux != NULL) {
		printf("%c\n", aux->item);
		aux = aux->next;
	}
	printf("===========\n");
}

void destroy(list **l) {
	node *aux = (*l)->root;
	node *next;

	while (aux != NULL) {
		next = aux->next;
		free(aux);
		aux = next;
	}

	free(*l);
	*l = NULL;
}
