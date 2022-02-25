#include <stdio.h>

#include "jun_str.h"

int main() {
  Str* a = jun_str_create("hello");
  Str* b = jun_str_create("world");

  jun_str_print(a);

  jun_str_starts_with(a, "hel") ? printf("YES1!\n") : printf("No1!\n");

  jun_str_ends_with(b, "poi") ? printf("YES2!\n") : printf("No2!\n");

  jun_str_append(b, " nice");
  jun_str_print(b);

  jun_str_cat(a, b);
  jun_str_print(a);

  jun_str_destroy(a);
  jun_str_destroy(b);
}
