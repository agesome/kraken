#include <string.h>

size_t
strlen (const char *l)
{
	const char *s;

	for (s = l; *s; s++)
		;

	return s - l;
}

void *
memset (void *l, int c, size_t n)
{
	uint8_t *us = l;
	uint8_t uc = c;

	while (n-- != 0)
		*us++ = uc;

	return l;
}
