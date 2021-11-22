#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

#define CHUNK_SZIE 10
#define TYPE int

typedef struct {
  TYPE* data;
  size_t cap;
  size_t len;
} Stack;

Stack* stack_init();

void stack_push(Stack* stack, TYPE value);

TYPE stack_pop(Stack* stack);

TYPE stack_top(Stack* stack);

int stack_empty(Stack* stack);

#endif
