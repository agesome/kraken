#include <stdio.h>
#include <stdlib.h>

#include <kraken/screen.h>
#include <kraken/ps2.h>
#include <kraken/kbd.h>
#include <kraken/dtables.h>
#include <kraken/isr.h>
#include <kraken/timer.h>
#include <kraken/multiboot.h>
#include <kraken/panic.h>


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
kmain (uint32_t magic, multiboot_info_t * multiboot)
{
	kinit_screen ();

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	{
		screen_print ("PANIC!\n");
		return;
	}

	// multiboot_info_t * m = addr;
	screen_print ("kernel commandline: ");
	screen_print ((char *) multiboot->cmdline);
	screen_putchar ('\n');

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
		// if (_kbd_state.pressed[KEY_LALT])
			// screen_print ("ALT pressed!\n");
	}
}
