#ifndef STRING_H_
#define STRING_H_

typedef struct {
  char* data;
  int len;
} Str;

///
/// create a string
///
Str* jun_str_create(char* data);

///
/// destroy a string, set it to NULL
///
void jun_str_destroy(Str* str);

///
/// if out of bounds, return NULL;
///
char jun_str_at(Str* str, int i);

void jun_str_print(Str* str);

///
/// check if src contains sub, return 1 if true, else 0
///
int jun_str_contains(Str* src, char* sub);

int jun_str_starts_with(Str* src, char* start);

int jun_str_ends_with(Str* src, char* end);

void jun_str_cat(Str* lhs, Str* rhs);

void jun_str_append(Str* src, char* data);

#endif
