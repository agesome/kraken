#include <stdio.h>

int
putchar (int c)
{
	screen_putchar (c);
	return c;
}

void putc_ (void *p, char c)
{
	screen_putchar (c);
}