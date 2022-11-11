#ifndef STRING_H
#define STRING_H
#include "type.h"

char * strcpy(char * dest, const char * src);
char* strcat(char* const dest, const char* src);
size_t strlen(const char* str);
int strcmp(const char* lhs, const char* rhs);
char* strchr(const char* str, int ch);
char* strrchr(const char* str, int ch);

#endif