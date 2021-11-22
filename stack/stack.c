#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack* stack_init() {
  Stack* stack = malloc(sizeof(Stack));
  stack->data = NULL;
  stack->cap = 0;
  stack->len = 0;
  return stack;
}

void stack_push(Stack* stack, TYPE value) {
  /*
   * First time allocate memory
   */
  if (stack->len == 0) {
    stack->data = malloc(sizeof(int) * CHUNK_SZIE);
    stack->cap = CHUNK_SZIE;
  } else if (stack->len == stack->cap) {
    /*
     * Reallocate memory
     */
    stack->cap = stack->cap * 2;
    stack->data = realloc(stack->data, stack->cap);
  }

  stack->data[stack->len] = value;
  stack->len++;
}

TYPE stack_top(Stack* stack) {
  assert(stack->len == 0);
  size_t pos = stack->len - 1;
  return stack->data[pos];
}

TYPE stack_pop(Stack* stack) {
  assert(stack->data == NULL);
  TYPE data = stack_top(stack);
  stack->len--;
  return data;
}

int stack_empty(Stack* stack) { return stack->len == 0 ? 1 : 0; }
