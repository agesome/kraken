#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <kraken/screen.h>

#define NULL 0L
#define PRINTF_LONG_SUPPORT

void init_printf(void* putp,void (*putf) (void*,char));

void tfp_printf(char *fmt, ...);
void tfp_sprintf(char* s,char *fmt, ...);

void tfp_format(void* putp,void (*putf) (void*,char),char *fmt, va_list va);

#define printf tfp_printf 
#define sprintf tfp_sprintf 

int putchar (int c);
void putc_ (void *p, char c);

#endif // STDIO_H
