#ifndef V86_H
#define V86_H

#include <kraken/isr.h>

void v86_handler (registers_t regs);

void init_v86 (void);
#endif // V86_H
