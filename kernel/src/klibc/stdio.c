#include <stdio.h>

int
putchar (int c)
{
	screen_putchar (c);
	return c;
}
