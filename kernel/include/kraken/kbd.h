#ifndef KBD_H
#define KBD_H

#include <kraken/ps2.h>
#include <kraken/isr.h>
#include <kraken/screen.h>

enum
{
	NO_KEY = 128, KEY_LSHIFT, KEY_ENTER, KEY_RSHIFT, KEY_LALT,
	KEY_LIMIT
};

extern uint8_t set2_keys[];
extern bool _kbd_print_input; 

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
