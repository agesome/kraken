#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint.h>
#include <stdbool.h>

uint32_t kmalloc_(uint32_t, bool, uint32_t *);

#define kmalloca(sz) kmalloc_(sz, true, NULL)
#define kmallocp(sz, ph) kmalloc_(sz, false, ph)
#define kmallocap(sz, ph) kmalloc_(sz, true, ph)
#define kmalloc(sz) kmalloc_(sz, false, NULL)

#endif // KMALLOC_H