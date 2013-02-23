#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <ps2.h>
#include <kbd.h>
#include <dtables.h>
#include <isr.h>
#include <timer.h>

void
kinit_screen (void)
{
	screen_clear ();
	screen_setcursor (0, 0);
	screen_print ("kraken booting\n");
	if (screen_hascolor ())
		{
			screen_setcolor (LBROWN, LMAGENTA);
			screen_print ("color screen found\n");
			screen_defcolor ();
		}
}

void
kmain (unsigned long magic, unsigned long addr)
{
	kinit_screen ();
	init_gdt ();
	init_idt ();
	kbd_init ();
	init_timer (100);

	if (ps2_controller_init ())
		screen_print ("PS/2 cotroller OK\n");
	else
		screen_print ("PS/2 controller NOT OK\n");
	bool kbd, mouse;
	ps2_test_ports (&kbd, &mouse);
	if (kbd)
		screen_print ("keyboard present\n");
	if (mouse)
		screen_print ("mouse present\n");
	ps2_set_ports (kbd, mouse);
	ps2_reset_device (PS2_KBD);
	ps2_reset_device (PS2_MOUSE);

	// _kbd_print_input = false;

	__asm volatile ("sti");
	while (1)
	{
		if (_kbd_state.pressed[KEY_LALT])
			screen_print ("ALT pressed!\n");
	}
}
