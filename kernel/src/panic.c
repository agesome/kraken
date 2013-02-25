#include <kraken/panic.h>

void
panic (const char * s, const char *f, uint16_t line)
{
	printf ("\nPANIC: %s (at %s:%d)\n", s, f, line);
	while (true)
		__asm ("nop");
}
