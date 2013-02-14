#ifndef KBD_H
#define KBD_H

#include <ps2.h>

enum
{
	NO_KEY = 128, KEY_LSHIFT, KEY_ENTER, KEY_RSHIFT, KEY_LALT,
	KEY_LIMIT
};

#define NKEYS (sizeof(keys)/sizeof(key_t))

typedef struct {
	uint8_t sc;
	uint8_t v;
} key_t;

extern key_t keys[];

typedef struct
{
	bool pressed[KEY_LIMIT];
} kbd_t;

typedef union
{
	uint64_t v;
	uint8_t bytes[8];
} scancode_t;

kbd_t _kbd_state;

void kbd_init (void);
char kbd_decode_char (uint8_t);
uint8_t kbd_decode_scancode (scancode_t code);
bool kbd_get_scancode (scancode_t *);

#endif // KBD_H
