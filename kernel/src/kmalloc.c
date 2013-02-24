#include <kraken/kmalloc.h>

uint32_t placement_address;

uint32_t
kmalloc_(uint32_t sz, bool align, uint32_t *phys)
{
  if (align == 1 && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  if (phys)
  {
    *phys = placement_address;
  }
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
}