#include "jun_str.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Str* jun_str_create(char* data) {
  Str* str = (Str*)malloc(sizeof(Str));
  str->len = strlen(data);
  str->data = (char*)malloc(sizeof(char) * (str->len + 1));
  strcpy(str->data, data);
  return str;
}

///
/// destroy a string, set it to NULL
///
void jun_str_destroy(Str* str) {
  free(str->data);
  free(str);
  str = NULL;
}

///
/// if out of bounds, return NULL;
///
char jun_str_at(Str* str, int i) {
  if (i >= str->len || i < 0) {
    assert(0);
    return '\0';
  }
  return str->data[i];
}

void jun_str_print(Str* str) { printf("%s\n", str->data); };

///
/// check if src contains sub, return 1 if true, else 0
///
int jun_Str_contains(Str* src, Str* sub) {
  int result = 1;
  int index = 0;

  if (sub->len > src->len) {
    return 0;
  }

  while (index++ <= src->len - sub->len) {
    result = 1;
    for (int i = index - 1; i < sub->len; i++) {
      if (jun_str_at(src, i) != jun_str_at(sub, i)) {
        result = 0;
        break;
      }
    }
  }

  return result;
}

int jun_str_starts_with(Str* src, char* start) {
  int start_len = strlen(start);
  if (start_len > src->len) {
    return 0;
  }

  for (int i = 0; i < start_len; ++i) {
    if (jun_str_at(src, i) != start[i]) {
      return 0;
    }
  }
  return 1;
}

int jun_str_ends_with(Str* src, char* end) {
  int end_len = strlen(end);
  if (end_len > src->len) {
    return 0;
  }

  for (int i = end_len - 1; i >= 0; ++i) {
    if (jun_str_at(src, i) != end[i]) {
      return 0;
    }
  }

  return 1;
}

void jun_str_append(Str* src, char* data) {
  char* new_data = malloc(sizeof(char) * (strlen(data) + src->len + 1));
  int i;
  for (i = 0; i < src->len; ++i) {
    new_data[i] = src->data[i];
  }

  for (; i - src->len < strlen(data); ++i) {
    new_data[i] = data[i - src->len];
  }

  src->len = i;
  free(src->data);
  src->data = new_data;
}

void jun_str_cat(Str* lhs, Str* rhs) { jun_str_append(lhs, rhs->data); }
