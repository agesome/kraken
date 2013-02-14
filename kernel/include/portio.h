#ifndef PORTIO_H
#define PORTIO_H

#include <stdint.h>

void outb (uint16_t port, uint8_t value);
uint8_t inb (uint16_t port);
uint16_t inw (uint16_t port);

#define _BV(B) (1 << B)
#endif // PORTIO_H
