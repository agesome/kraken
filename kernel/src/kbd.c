#include <kbd.h>

// single-byte keys
key_t keys[] = {
	{ 0x15, 'q' }, { 0x1d, 'w' }, { 0x21, 'c' }, { 0x2d, 'r' }, { 0x31, 'n' },
	{ 0x35, 'y' }, { 0x4d, 'p' }, { 0x1a, 'z' }, { 0x22, 'x' }, { 0x2a, 'v' },
	{ 0x32, 'b' }, { 0x3a, 'm' }, { 0x42, 'k' }, { 0x1b, 's' }, { 0x2b, 'f' },
	{ 0x23, 'd' }, { 0x33, 'h' }, { 0x3b, 'j' }, { 0x43, 'i' }, { 0x4b, 'l' },
	{ 0x1c, 'a' }, { 0x24, 'e' }, { 0x2c, 't' }, { 0x34, 'g' }, { 0x3c, 'u' },
	{ 0x44, 'o' }, { 0x29, ' ' }, { 0x12, KEY_LSHIFT }, { 0x5a, KEY_ENTER },
	{ 0x59, KEY_RSHIFT }, { 0x11, KEY_LALT }, { 0x66, '\b' }, { 0x0d, '\t' }
};

void
kbd_init ()
{
	for (int i = 0; i < KEY_LIMIT; i++)
		_kbd_state.pressed[i] = false;
}

char
kbd_decode_char (uint8_t code)
{
	for (int i = 0; i < sizeof(keys) / sizeof(key_t); i++)
		if (keys[i].sc == code)
			return keys[i].v;
	return 0;
}

uint8_t
kbd_decode_scancode (const scancode_t code)
{
	int i, bi = 0;
	uint8_t byte = code.bytes[bi++];
	bool done = false;
	bool release = false;

	do
	{
		switch (byte)
		{
			case 0xe0: break; // media/keypad
			case 0xf0: release = true; break;
			default:
			{
				if (bi > 2) // multibyte scancode
					return NO_KEY;
				for (i = 0; i <= NO_KEY && keys[i].sc != byte; i++);
				if ((i - 1) == NO_KEY) // haha; also, unknown key
					return NO_KEY;
				_kbd_state.pressed[keys[i].v] = !release;
				if (release)
					return NO_KEY;
				return keys[i].v;
			}
		}
		byte = code.bytes[bi++];
	}
	while (!done && bi < 8);
	return NO_KEY;
}

bool
kbd_get_scancode (scancode_t *s)
{
	uint8_t v;
	uint8_t i = 0;

	while (ps2_device_read (&v))
		s->bytes[i++] = v;
	if (!i)
		return false;
	return true;
}