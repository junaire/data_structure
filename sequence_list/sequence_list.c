#include "sequence_list.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

SequenceList* list_init() {
  SequenceList* list = malloc(sizeof(SequenceList));
  list->data = NULL;
  list->cap = 0;
  list->len = 0;
  return list;
}

void list_clear(SequenceList* list) {
  free(list->data);
  list->cap = 0;
  list->len = 0;
}

void list_destroy(SequenceList* list) {
  list_clear(list);
  free(list);
}

size_t list_length(SequenceList* list) { return list->len; }

TYPE list_index(SequenceList* list, size_t pos) {
  if (pos < 0 || pos > list->len) {
    assert("Bad index");
  }
  return list->data[pos];
}

void list_insert(SequenceList* list, TYPE value, size_t pos) {
  /*
   * First time allocate memory
   */
  if (list->len == 0) {
    list->data = malloc(sizeof(int) * CHUNK_SZIE);
    list->cap = CHUNK_SZIE;
  } else if (list->len == list->cap) {
    /*
     * Reallocate memory
     */
    list->cap = list->cap * 2;
    list->data = realloc(list->data, list->cap);
  }

  /*
   * | 1 | 2 | 3 | 4 | 5 | 6 |
   *              ^
   *              |
   *            | 8 |
   */
  if (pos != list->len) {
    memmove(list->data + pos + 1, list->data + pos,
            (list->len - pos) * sizeof(int));
  }

  list->data[pos] = value;
  list->len++;
}

void list_delete_node(SequenceList* list, size_t pos) {
  memmove(list->data + pos, list->data + pos + 1,
          (list->len - pos) * sizeof(int));
  list->len--;
}

void list_merge(SequenceList* l, SequenceList* o) {
  l->data = realloc(l->data, sizeof(TYPE) * (l->len + o->len));
  l->cap = l->len + o->len;
  for (int i = 0; i < o->len; i++) {
    l->data[l->len + i] = o->data[i];
  }

  free(o->data);
  o->data = NULL;
  o->len = o->cap = 0;
}

