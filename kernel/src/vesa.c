#include <kraken/vesa.h>

bool
vbe_get_info (vbeInfo_t * vi)
{
	strncpy ((char *) vi->signature, "VBE2", 4);
	uint32_t addr = (uint32_t) vi;
	uint16_t seg = (addr >> 16);
	uint16_t off = (addr & 0xffff);

	__asm volatile (
					"pusha;"
					"mov %0, %%es;"
					"mov %1, %%di;"
					"mov $0xf400, %%ax;"
					"int $0x10;"
					"popa;"
					:
					: "r" (seg), "r" (off)
					: "eax");
	return true;
}