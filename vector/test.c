#include "vector.h"

int main() {
  Vector* vector = jun_vector_init();
  jun_vector_append(vector, 1);
  printf("vector push 1\n");
  jun_vector_append(vector, 2);
  printf("vector push 2\n");
  jun_vector_append(vector, 3);
  printf("vector push 3\n");
  jun_vector_append(vector, 4);
  printf("vector push 4\n");
  jun_vector_append(vector, 5);
  printf("vector push 5\n");
  printf("vector:\n");
  jun_vector_print(vector);

  jun_vector_insert(vector, 100, 2);
  printf("vector after insert 100 at 2:\n");
  jun_vector_print(vector);
  printf("vector delete node at 4\n");
  jun_vector_delete_node(vector, 4);
  jun_vector_print(vector);

  jun_vector_reverse(vector);
  printf("vector reverse:\n");
  jun_vector_print(vector);
  printf("vector after insert 99 at 0:\n");
  jun_vector_insert(vector, 99, 0);

  jun_vector_sort(vector);
  printf("vector after sort:\n");
  jun_vector_print(vector);

  jun_vector_destroy(vector);
}
