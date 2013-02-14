#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <ps2.h>
#include <kbd.h>
#include <dtables.h>

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
	init_gdt ();
	init_idt ();
	kinit_screen ();

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

	char buf[10];
	uint8_t c;
	buf[1] = '\0';
	while (1)
		{
			if (ps2_device_read (&c))
				{
					if (c == 0xf0) // released
						{
							ps2_device_read (&c);
							continue;
						}
					buf[0] = kbd_decode (c);
					screen_print (buf);
					// itoa (c, buf, 16);
					// screen_print (buf);
					// screen_print (" ");
				}
		}

	// if (atoi ("wee1234") == 1234)
	// screen_print ("Success.");
	// asm volatile ("int $0x3");

	/* printf ("Whee! %d '%s' \n", 1234, "testing printf"); */
}
