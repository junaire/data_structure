#include <stdio.h>

#include "queue.h"

int main() {
  Queue* queue = jun_queue_init();
  jun_queue_push(queue, 1);
  printf("push 1 to queue\n");
  jun_queue_push(queue, 2);
  printf("push 2 to queue\n");
  jun_queue_push(queue, 3);
  printf("push 3 to queue\n");
  jun_queue_push(queue, 4);
  printf("push 4 to queue\n");
  jun_queue_push(queue, 5);
  printf("push 5 to queue\n");

  printf("Queue:\n");
  jun_queue_print(queue);

  jun_queue_pop(queue);
  printf("pop!\n");
  printf("Queue:\n");
  jun_queue_print(queue);
  jun_queue_pop(queue);
  jun_queue_pop(queue);
  printf("Queue:\n");
  jun_queue_print(queue);

  printf("queue front = %d\n", jun_queue_front(queue)->value);
  printf("queue back = %d\n", jun_queue_back(queue)->value);

  jun_queue_destroy(queue);
}
