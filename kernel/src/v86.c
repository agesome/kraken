#include <kraken/v86.h>

void
v86_handler (registers_t regs)
{
	printf ("v86!\n");
	regs.eflags |= (1 << 17);
}

void
init_v86 (void)
{
	register_interrupt_handler (0x80, &v86_handler);
}
