#ifndef QUEUE_H_
#define QUEUE_H_

#define TYPE int

typedef struct _Node {
  TYPE value;
  struct _Node *prev;
  struct _Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  unsigned long length;
} Queue;

Queue *jun_queue_init();

void jun_queue_print(Queue *queue);

void jun_queue_push(Queue *queue, TYPE value);

void jun_queue_pop(Queue *queue);

Node *jun_queue_front(Queue *queue);

Node *jun_queue_back(Queue *queue);

void jun_queue_clear(Queue *queue);

void jun_queue_destroy(Queue *queue);

unsigned long jun_queue_length(Queue *queue);

#endif
