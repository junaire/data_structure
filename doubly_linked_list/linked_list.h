#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

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
} List;

List *jun_list_init();

void jun_list_print(List *list);

void jun_list_append(List *list, TYPE value);

void jun_list_insert(List *list, TYPE value);

void jun_list_clear(List *list);

void jun_list_destroy(List *list);

void jun_list_merge(List *l, List *o);

unsigned long jun_list_length(List *list);

// get node in the list, the first one starts with index 0
Node *jun_list_get_node(List *list, unsigned long index);

int jun_list_node_index(List *list, TYPE value);

void jun_list_reverse(List *list);

void jun_list_partial_reverse(List *list, int beg, int end);

// sort the list, flag
void jun_list_sort(List *list);

int jun_list_node_count(List *list, TYPE value);

#endif
