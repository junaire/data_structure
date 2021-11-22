#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

List *list_init() {
  List *list = malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
  return list;
}

void list_append(List *list, void *value) {
  Node *node = malloc(sizeof(Node));
  node->value = value;

  if (list->length == 0) {
    list->head = list->tail = node;
    node->prev = NULL;
    node->next = NULL;
  }

  list->tail->next = node;
  node->prev = list->tail;
  list->tail = node;
  list->length++;
}

void list_insert(List *list, void *value) {
  Node *node = malloc(sizeof(Node));
  node->value = value;
  if (list->length == 0) {
    list->head = list->tail = node;
    node->prev = NULL;
    node->next = NULL;
  }

  list->head->prev = node;
  node->next = list->head;
  list->head = node;
  list->length++;
}

void list_clear(List *list) {
  Node *iter = list->head;
  Node *tmp = NULL;
  if (list->length == 0) {
    return;
  }
  while (iter != list->tail) {
    tmp = iter->next;
    free(iter);
  }
  free(iter);
}

void list_destroy(List *list) {
  list_clear(list);
  free(list);
}

unsigned long list_length(List *list) { return list->length; }

void list_merge(List *l, List *o) {
  if (list_length(o) == 0) {
    return;
  }
  o->head->prev = l->tail;

  l->tail = o->tail;
  l->length += o->length;

  o->head = o->tail = NULL;
  o->length = 0;
}

Node *list_index(List *list, unsigned long index) {
  Node *res = NULL;
  if (index <= 0) {
    return res;
  }

  res = list->head;
  while (index-- && res) {
    res = res->next;
  }
  return res;
}
