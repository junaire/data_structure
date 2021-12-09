#include "string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Str* Str_create(char* data) {
  Str* str = (Str*)malloc(sizeof(Str));
  str->len = strlen(data);
  str->data = (char*)malloc(sizeof(char) * (str->len + 1));
  strcpy(str->data, data);
  return str;
}

///
/// destroy a string, set it to NULL
///
void Str_destroy(Str* str) {
  free(str->data);
  free(str);
  str = NULL;
}

///
/// if out of bounds, return NULL;
///
char Str_at(Str* str, int i) {
  if (i >= str->len || i < 0) {
    assert(0);
    return '\0';
  }
  return str->data[i];
}

void Str_print(Str* str) { printf("%s\n", str->data); };

///
/// check if src contains sub, return 1 if true, else 0
///
int Str_contains(Str* src, Str* sub) {
  int result = 1;
  int index = 0;

  if (sub->len > src->len) {
    return 0;
  }

  while (index++ <= src->len - sub->len) {
    result = 1;
    for (int i = index - 1; i < sub->len; i++) {
      if (Str_at(src, i) != Str_at(sub, i)) {
        result = 0;
        break;
      }
    }
  }

  return result;
}
