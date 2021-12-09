#ifndef STRING_H_
#define STRING_H_

typedef struct {
  char* data;
  int len;
} Str;

///
/// create a string
///
Str* Str_create(char* data);

///
/// destroy a string, set it to NULL
///
void Str_destroy(Str* str);

///
/// if out of bounds, return NULL;
///
char Str_at(Str* str, int i);

void Str_print(Str* str);

///
/// check if src contains sub, return 1 if true, else 0
///
int Str_contains(Str* src, Str* sub);
#endif
