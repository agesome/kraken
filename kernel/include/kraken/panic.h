#ifndef PANIC_H
#define PANIC_H

#include <kraken/screen.h>
#include <stdbool.h>
#include <stdio.h>

#define PANIC(m) panic (m, __FILE__, __LINE__);
void panic (const char *, const char *, uint16_t);

#endif // PANIC_H