#include <kraken/panic.h>

void
panic (const char * s)
{
	screen_putchar ('\n');
	screen_print (s);
	screen_putchar ('\n');
	while (true)
		__asm ("nop");
}
