#include <kraken/panic.h>

void
panic (const char * s)
{
	screen_print ("\nPANIC: ");
	screen_print (s);
	screen_putchar ('\n');
	while (true)
		__asm ("nop");
}
