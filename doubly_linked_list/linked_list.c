#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

List *jun_list_init() {
  List *list = malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
  return list;
}

void jun_list_print(List *list) {
  Node *iter = list->head;
  while (iter != NULL) {
    printf("%d\t", iter->value);
    iter = iter->next;
  }
  printf("\n");
}

void jun_list_append(List *list, TYPE value) {
  Node *node = malloc(sizeof(Node));
  node->value = value;

  if (list->length == 0) {
    list->head = list->tail = node;
    node->prev = NULL;
    node->next = NULL;
  } else {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
  }

  list->length++;
}

void jun_list_insert(List *list, TYPE value) {
  Node *node = malloc(sizeof(Node));
  node->value = value;
  if (list->length == 0) {
    list->head = list->tail = node;
    node->prev = NULL;
    node->next = NULL;
  } else {
    list->head->prev = node;
    node->next = list->head;
    list->head = node;
  }

  list->length++;
}

void jun_list_clear(List *list) {
  if (list->length == 0) {
    return;
  }

  if (list->length == 1) {
    free(list->head);
    list->head = list->tail = NULL;
    list->length = 0;
    return;
  }

  Node *iter = list->head;
  Node *del;
  while (iter != NULL) {
    del = iter;
    iter = iter->next;
    free(del);
  }

  list->length = 0;
}

void jun_list_destroy(List *list) {
  jun_list_clear(list);
  free(list);
}

unsigned long jun_list_length(List *list) { return list->length; }

void jun_list_merge(List *l, List *o) {
  if (jun_list_length(o) == 0) {
    return;
  }
  o->head->prev = l->tail;

  l->tail = o->tail;
  l->length += o->length;

  o->head = o->tail = NULL;
  o->length = 0;
}

Node *jun_list_get_node(List *list, unsigned long index) {
  Node *res = NULL;
  if (index < 0) {
    return res;
  }

  res = list->head;
  while (index-- && res) {
    res = res->next;
  }
  return res;
}

void jun_list_sort(List *list) {
  for (int i = 0; i < list->length - 1; ++i) {
    for (int j = 0; j < list->length - i - 1; ++j) {
      Node *lhs = jun_list_get_node(list, j);
      Node *rhs = jun_list_get_node(list, j + 1);

      if (lhs->value > rhs->value) {
        TYPE tmp = lhs->value;
        lhs->value = rhs->value;
        rhs->value = tmp;
      }
    }
  }
}

int jun_list_node_count(List *list, TYPE value) {
  Node *iter = list->head;
  int cnt = 0;
  while (iter != NULL) {
    if (iter->value == value) {
      cnt++;
    }
    iter = iter->next;
  }
  return cnt;
}

void jun_list_partial_reverse(List *list, int beg, int end) {
  if (beg >= end) {
    return;
  }
  if (beg < 0 || end >= list->length) {
    return;
  }

  Node *beg_node = list->head;
  int index = 0;

  while (index++ < beg) {
    beg_node = beg_node->next;
  }

  Node *end_node = beg_node->next;

  while (index++ < end) {
    end_node = end_node->next;
  }

  /*
   +-------------------------------------+
   | beg_node | 1 | 2 | 3 | 4 | end_node |
   +-------------------------------------+
   */

  while ((beg_node != end_node->prev) && (beg_node->next != end_node->prev)) {
    TYPE tmp = beg_node->value;
    beg_node->value = end_node->value;
    end_node->value = tmp;

    beg_node = beg_node->next;
    end_node = end_node->prev;
  }
}

void jun_list_reverse(List *list) {
  Node *beg_node = list->head;
  Node *end_node = list->tail;

  while ((beg_node != end_node->prev) && (beg_node->next != end_node->prev)) {
    TYPE tmp = beg_node->value;
    beg_node->value = end_node->value;
    end_node->value = tmp;

    beg_node = beg_node->next;
    end_node = end_node->prev;
  }
}

