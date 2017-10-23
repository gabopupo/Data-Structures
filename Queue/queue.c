#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue *create() {
	queue *q = (queue *) malloc (sizeof(queue));
	if (q != NULL) {
		q->front = q->rear = NULL;
		q->size = 0;
	}
	return q;
}

void enqueue(queue *q, int it) {
	node *enq = (node *) malloc (sizeof(node));

	if (enq != NULL) {
		enq->item = it;
		enq->prev = NULL;

		if (q->front == NULL) {
			q->front = q->rear = enq;
		} else {
			q->rear->prev = enq;
			q->rear = enq;
		}
		++(q->size);
	}
}

void dequeue(queue *q) {
	if (q != NULL && !empty(q)) {
		node *deq = q->front;
		q->front = deq->prev;
		--(q->size);
		free(deq);
	}
}

node *front(queue *q) {
	return q->front;
}

int empty(queue *q) {
	return (q->size == 0);
}

void destroy(queue **q) {
	while (!empty(*q)) dequeue(*q);
	free(*q);
	*q = NULL;
}

void print_queue(queue *q) {
	node *aux = q->front;

	while (aux != NULL) {
		printf("%d ", aux->item);
		aux = aux->prev;
	}
}
