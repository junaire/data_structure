#include <stdio.h>

#include "linked_list.h"

int main() {
  List* list = jun_list_init();
  for (int i = 0; i < 5; ++i) {
    jun_list_append(list, i * 2 + 3);
  }

  for (int i = 1; i < 10; i *= 2) {
    jun_list_insert(list, i);
  }

  jun_list_print(list);

  int i = 1;
  printf("The %d node is %d\n", i, jun_list_get_node(list, i)->value);

  printf("sort the list:\n");
  jun_list_sort(list);
  jun_list_print(list);

  printf("value 4 occurs %d times\n", jun_list_node_count(list, 4));

  printf("reverse the list:\n");
  jun_list_reverse(list);
  jun_list_print(list);

  printf("partially reverse the list:\n");
  jun_list_partial_reverse(list, 0, 3);
  jun_list_print(list);

  jun_list_clear(list);

  printf("list length = %lu\n", jun_list_length(list));

  jun_list_append(list, 1);
  jun_list_print(list);

  jun_list_destroy(list);
}
