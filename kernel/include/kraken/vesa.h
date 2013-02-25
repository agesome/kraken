#ifndef VESA_H
#define VESA_H

#include <stdint.h>

#define FARPTR(v) (v[0] + v[1]*16)

typedef struct vesaInfo
{
	uint8_t 	signature[4];
	uint16_t 	version;
	uint16_t 	oemStringPtr[2];
	uint8_t 	capabilities[4];
	uint16_t 	videomodes[2];
	uint16_t 	totalMemory; // 64K blocks
	uint16_t	oemSoftwareRev;
	uint16_t	oemVendorNamePtr[2];
	uint16_t	oemProductNamePtr[2];
	uint16_t	oemProductRevPtr[2];
	uint16_t	reserved[111];
	uint8_t		oemData[256];
} __attribute__ ((packed)) vesaInfo_t;

#endif // VESA_H