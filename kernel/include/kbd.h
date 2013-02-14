#ifndef KBD_H
#define KBD_H

#include <ps2.h>

typedef struct {
	uint8_t sc;
	char v;
} key_t;

extern key_t keys[];

char kbd_decode (uint8_t);
#endif // KBD_H
