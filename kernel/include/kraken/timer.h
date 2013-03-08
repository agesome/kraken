#ifndef TIMER_H
#define TIMER_H

#include <kraken/portio.h>
#include <kraken/isr.h>
#include <stdio.h>

void init_timer (uint32_t frequency);

extern uint32_t tick;
#endif // TIMER_H
