#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

Queue *jun_queue_init() {
  Queue *queue = malloc(sizeof(Queue));
  queue->head = NULL;
  queue->tail = NULL;
  queue->length = 0;
  return queue;
}

void jun_queue_print(Queue *queue) {
  Node *iter = queue->head;
  while (iter != NULL) {
    printf("%d\t", iter->value);
    iter = iter->next;
  }
  printf("\n");
}

void jun_queue_push(Queue *queue, TYPE value) {
  Node *node = malloc(sizeof(Node));
  node->value = value;
  if (queue->length == 0) {
    queue->head = queue->tail = node;
    node->prev = NULL;
    node->next = NULL;
  } else {
    queue->head->prev = node;
    node->next = queue->head;
    queue->head = node;
  }

  queue->length++;
}

void jun_queue_clear(Queue *queue) {
  if (queue->length == 0) {
    return;
  }

  if (queue->length == 1) {
    free(queue->head);
    queue->head = queue->tail = NULL;
    queue->length = 0;
    return;
  }

  Node *iter = queue->head;
  Node *del;
  while (iter != NULL) {
    del = iter;
    iter = iter->next;
    free(del);
  }

  queue->length = 0;
}

void jun_queue_destroy(Queue *queue) {
  jun_queue_clear(queue);
  free(queue);
}

unsigned long jun_queue_length(Queue *queue) { return queue->length; }

void jun_queue_pop(Queue *queue) {
  if (queue->length == 0) {
    return;
  }
  if (queue->length == 1) {
    queue->head = queue->tail = NULL;
  } else {
    Node *new_tail = queue->tail->prev;
    free(queue->tail);
    queue->tail = new_tail;
    new_tail->next = NULL;
  }
  queue->length--;
}

Node *jun_queue_front(Queue *queue) { return queue->head; }

Node *jun_queue_back(Queue *queue) { return queue->tail; }
