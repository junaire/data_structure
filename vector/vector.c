#include "vector.h"

#include <stdlib.h>
#include <string.h>

Vector* jun_vector_init() {
  Vector* vector = malloc(sizeof(Vector));
  vector->data = NULL;
  vector->cap = 0;
  vector->len = 0;
  return vector;
}

void jun_vector_clear(Vector* vector) {
  free(vector->data);
  vector->cap = 0;
  vector->len = 0;
}

void jun_vector_destroy(Vector* vector) {
  jun_vector_clear(vector);
  free(vector);
  vector = NULL;
}

size_t jun_vector_length(Vector* vector) { return vector->len; }

// start from index 0
TYPE jun_vector_get_node(Vector* vector, size_t pos) {
  return vector->data[pos];
}

// start from index 0
void jun_vector_insert(Vector* vector, TYPE value, size_t pos) {
  /*
   * First time allocate memory
   */
  if (vector->cap == 0) {
    vector->data = malloc(sizeof(TYPE) * CHUNK_SZIE);
    vector->cap = CHUNK_SZIE;
  } else if (vector->len == vector->cap) {
    /*
     * Reallocate memory
     */
    vector->cap = vector->cap * 2;
    vector->data = realloc(vector->data, vector->cap);
  }

  /*   0   1   2   3   4   5
   * | 5 | 9 | 1 | 8 | 7 | 0 |
   *              ^
   *              |
   *            | 2 |
   */
  if (pos != vector->len) {
    memmove(vector->data + pos + 1, vector->data + pos,
            (vector->len - pos) * sizeof(TYPE));
  }

  vector->data[pos] = value;
  vector->len++;
}

void jun_vector_append(Vector* vector, TYPE value) {
  jun_vector_insert(vector, value, jun_vector_length(vector));
}

void jun_vector_delete_node(Vector* vector, size_t pos) {
  memmove(vector->data + pos - 1, vector->data + pos,
          (vector->len - pos) * sizeof(TYPE));
  vector->len--;
}

void jun_vector_merge(Vector* l, Vector* o) {
  l->data = realloc(l->data, sizeof(TYPE) * (l->len + o->len));
  l->cap = l->len + o->len;
  for (int i = 0; i < o->len; i++) {
    l->data[l->len + i] = o->data[i];
  }

  free(o->data);
  o->data = NULL;
  o->len = o->cap = 0;
}

TYPE jun_vector_back(Vector* vector) {
  return jun_vector_get_node(vector, jun_vector_length(vector));
}

TYPE jun_vector_front(Vector* vector) { return jun_vector_get_node(vector, 0); }

void jun_vector_sort(Vector* vector) {
  for (int i = 0; i < vector->len; ++i) {
    for (int j = 0; j < vector->len - i - 1; ++j) {
      TYPE m = jun_vector_get_node(vector, j);
      TYPE n = jun_vector_get_node(vector, j + 1);
      if (m > n) {
        TYPE tmp = m;
        vector->data[j] = n;
        vector->data[j + 1] = m;
      }
    }
  }
}

void jun_vector_reverse(Vector* vector) {
  TYPE* beg = vector->data;
  TYPE* end = vector->data + vector->len - 1;

  while (beg < end) {
    TYPE tmp = *beg;
    *beg = *end;
    *end = tmp;

	beg++;
	end--;
  }
}

void jun_vector_print(Vector* vector) {
  for (int i = 0; i < vector->len; ++i) {
    // FIXME: It only works when TYPE is int
    printf("%d\t", jun_vector_get_node(vector, i));
  }
  printf("\n");
}
