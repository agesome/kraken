#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

size_t strlen (const char *l);
void * memset (void *l, int c, size_t n);
char * strncpy (char *, const char *, size_t);
#endif // STRING_H
