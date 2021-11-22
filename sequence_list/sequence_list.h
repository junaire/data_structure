#ifndef SEQUENCE_LIST_H_
#define SEQUENCE_LIST_H_

#include <stdio.h>

#define CHUNK_SZIE 10
#define TYPE int

typedef struct {
  TYPE* data;
  size_t cap;
  size_t len;
} SequenceList;

SequenceList* list_init();

void list_clear(SequenceList* list);

void list_destroy(SequenceList* list);

size_t list_length(SequenceList* list);

TYPE list_index(SequenceList* list, size_t pos);

void list_insert(SequenceList* list, TYPE value, size_t pos);

void list_delete_node(SequenceList* list, size_t pos);

void list_merge(SequenceList* l, SequenceList* o);

#endif
