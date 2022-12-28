// Copyright 2022 Ivan Sushin <i.suschin@yamdex.ru>

#include "string.hpp"

int size(const char* str1) {
  int size = 0;
  while (str1[size] != '\0') size++;
  return size;
}

// first part
char* CopyString(const char* str) {
  char* new_str = new char[size(str) + 1];
  if (*str != '\0') {
    memcpy(new_str, str, size(str));
    new_str[size(str)] = 0;
    return new_str;
  } else
    return nullptr;
}

// second part
char* ConcatinateStrings(const char* a, const char* b) {
  char* new_a = CopyString(a);
  size_t i, j;
  for (i = 0; a[i] != '\0'; i++)
    ;
  if (new_a) {
    for (j = 0; b[j] != '\0'; j++) new_a[i + j] = b[j];
    new_a[i + j] = '\0';
    return new_a;
  } else
    return nullptr;
}
