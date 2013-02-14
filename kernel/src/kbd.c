#include <kbd.h>

key_t keys[] = {
	{ 0x15, 'q' }, { 0x1d, 'w' }, { 0x21, 'c' }, { 0x2d, 'r' }, { 0x31, 'n' }, { 0x35, 'y' },
	{ 0x4d, 'p' }, { 0x1a, 'z' }, { 0x22, 'x' }, { 0x2a, 'v' }, { 0x32, 'b' }, { 0x3a, 'm' },
	{ 0x42, 'k' }, { 0x1b, 's' }, { 0x2b, 'f' }, { 0x23, 'd' }, { 0x33, 'h' }, { 0x3b, 'j' },
	{ 0x43, 'i' }, { 0x4b, 'l' }, { 0x1c, 'a' }, { 0x24, 'e' }, { 0x2c, 't' }, { 0x34, 'g' },
	{ 0x3c, 'u' }, { 0x44, 'o' }, { 0x29, ' ' }
};

void
kbd_init ()
{
}

char
kbd_decode (uint8_t code)
{
	int i;

	for (int i = 0; i < sizeof(keys) / sizeof(key_t); i++)
		if (keys[i].sc == code)
			return keys[i].v;
	return 0;
}
