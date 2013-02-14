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
	kbd_init ();

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
	uint8_t v;
	buf[1] = '\0';
	scancode_t c;
	while (1)
		{
			if (!kbd_get_scancode (&c))
				continue;
			v = kbd_decode_scancode (c);
			if (v == NO_KEY)
				continue;
			if (v == KEY_ENTER)
			{
				buf[1] = '\0';
				buf[0] = '\n';
				screen_print (buf);
			}
			else if (v < NO_KEY)
			{
				buf[1] = '\0';
				buf[0] = v;
				screen_print (buf);
			}
			// else
			// {
			// 	itoa (v, buf, 16);
			// }


			if (_kbd_state.pressed[KEY_LALT] && _kbd_state.pressed['q'])
				screen_print ("\nAlt + Q pressed!\n");
			// screen_print (" ");
			// if (ps2_device_read (&c))
			// 	{
			// 		if (c == 0xf0) // released
			// 			{
			// 				ps2_device_read (&c);
			// 				continue;
			// 			}
			// 		buf[0] = kbd_decode_char (c);
			// 		screen_print (buf);
			// 		// itoa (c, buf, 16);
			// 		// screen_print (buf);
			// 		// screen_print (" ");
			// 	}
		}

	// if (atoi ("wee1234") == 1234)
	// screen_print ("Success.");
	// asm volatile ("int $0x3");

	/* printf ("Whee! %d '%s' \n", 1234, "testing printf"); */
}
