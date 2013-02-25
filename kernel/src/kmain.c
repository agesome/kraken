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
#include <kraken/vesa.h>

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
vbe_info (vesaInfo_t * vi)
{
	screen_print ("Have VBE info\n");
	printf ("VBE signature: %s\n", vi->signature);
	printf ("VBE version: %x\n", vi->version);
	printf ("OEM software rev.: %d\n", vi->oemSoftwareRev);
	printf ("OEM string: %s\n", (char *) FARPTR (vi->oemStringPtr));
	printf ("OEM string: %s\n", (char *) FARPTR (vi->oemVendorNamePtr));
	printf ("OEM string: %s\n", (char *) FARPTR (vi->oemProductNamePtr));
	printf ("OEM string: %s\n", (char *) FARPTR (vi->oemProductRevPtr));
	printf ("Video memory, KB: %d\n", vi->totalMemory * 64);
}

void
kmain (uint32_t magic, multiboot_info_t * mbi)
{
	kinit_screen ();

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		panic ("magic mismatch!");

	init_idt ();
	init_gdt ();
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

	if (mbi->flags & MULTIBOOT_INFO_VIDEO_INFO)
		vbe_info ((vesaInfo_t *) mbi->vbe_control_info);
	else
		screen_print ("No VBE info from multiboot!\n");

	// __asm volatile ("sti");
	while (1);
}
