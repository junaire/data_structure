#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>

#define CHUNK_SZIE 10
#define TYPE int

typedef struct {
  TYPE* data;
  size_t cap;
  size_t len;
} Vector;

Vector* jun_vector_init();

void jun_vector_clear(Vector* vector);

void jun_vector_destroy(Vector* vector);

size_t jun_vector_length(Vector* vector);

void jun_vector_insert(Vector* vector, TYPE value, size_t pos);

void jun_vector_append(Vector* vector, TYPE value);

TYPE jun_vector_get_node(Vector* vector, size_t pos);

int jun_vector_index(Vector* vector, TYPE value);

void jun_vector_delete_node(Vector* vector, size_t pos);

void jun_vector_merge(Vector* l, Vector* o);

TYPE jun_vector_back(Vector* vector);

TYPE jun_vector_front(Vector* vector);

void jun_vector_sort(Vector* vector);

void jun_vector_reverse(Vector* vector);

void jun_vector_print(Vector* vector);

#endif
