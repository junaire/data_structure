#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct _Node {
  void *value;
  struct _Node *prev;
  struct _Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  unsigned long length;
} List;

List *list_init();

void list_append(List *list, void *value);

void list_insert(List *list, void *value);

void list_clear(List *list);

void list_destroy(List *list);

void list_merge(List *l, List *o);

unsigned long list_length(List *list);

Node *list_index(List *list, unsigned long index);

#endif
