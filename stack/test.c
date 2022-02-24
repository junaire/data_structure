#include "stack.h"

int main() {
  Stack* stack = jun_stack_init();
  jun_stack_push(stack, 1);
  printf("push 1 to the stack\n");
  jun_stack_push(stack, 2);
  printf("push 2 to the stack\n");
  jun_stack_push(stack, 3);
  printf("push 3 to the stack\n");

  printf("top = %d\n", jun_stack_top(stack));

  jun_stack_pop(stack);
  printf("pop!\n");

  printf("top = %d\n", jun_stack_top(stack));
  jun_stack_push(stack, 4);
  printf("push 4 to the stack\n");

  while (!jun_stack_empty(stack)) {
    jun_stack_pop(stack);
  }

  jun_stack_empty(stack) ? printf("Stack empty!\n")
                         : printf("Stack not empty\n");
}
