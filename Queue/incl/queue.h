#ifndef QUEUE_H
#define QUEUE_H

typedef struct node node;

struct node {
	int item;
	node *prev;
};

typedef struct queue queue;

struct queue {
	node *front, *rear;
	int size;
};

queue *create();
void enqueue(queue *, int);
void dequeue(queue *);
node *front(queue *);
int empty(queue *);
void destroy(queue **);
void print_queue(queue *);

#endif
