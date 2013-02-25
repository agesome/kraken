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

char *
strncpy (char *dest, const char *src, size_t n)
{
	size_t i;
	
	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';

	return dest;
}
