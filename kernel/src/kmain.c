#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <kraken/screen.h>
#include <kraken/ps2.h>
#include <kraken/kbd.h>
#include <kraken/dtables.h>
#include <kraken/isr.h>
#include <kraken/timer.h>
#include <kraken/multiboot.h>
#include <kraken/panic.h>
#include <kraken/vesa.h>
#include <kraken/v86.h>

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
	init_printf (NULL, putc_);
}

void
vbe_info (vbeInfo_t * vi)
{
	screen_print ("Have VBE info\n");
	printf ("VBE signature: %s\n", vi->signature);
	printf ("VBE version: %x\n", vi->version);
	printf ("OEM software rev.: %d\n", vi->oemSoftwareRev);
	printf ("OEM string: %s\n", (char *) FARPTR (vi->oemStringPtr));
	printf ("Video memory, KB: %d\n", vi->totalMemory * 64);
}

void
kmain (uint32_t magic, multiboot_info_t * mbi)
{
	init_descriptor_tables ();
	kinit_screen ();
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		PANIC ("magic mismatch!");

	__asm volatile ("sti;");
	init_timer (100);
	if (!ps2_controller_init ())
		screen_print ("PS/2 controller NOT OK\n");
	else
		kbd_init ();

	init_v86 ();
	__asm volatile ("int $0x80;");

	vbeInfo_t info;
	vbe_get_info (&info);
	vbe_info (&info);

	printf ("returned!\n");
	while (1)
		;
}
