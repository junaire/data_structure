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

Stack* jun_stack_init();

void jun_stack_push(Stack* stack, TYPE value);

TYPE jun_stack_pop(Stack* stack);

TYPE jun_stack_top(Stack* stack);

int jun_stack_empty(Stack* stack);

#endif
