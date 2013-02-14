#include <screen.h>
#include <interrupts.h>


void isr_handler (registers_t regs)
{
	screen_print ("Ooh, interrupt!\n");
	/* monitor_write_dec(regs.int_no); */
	/* monitor_put('\n'); */
}
