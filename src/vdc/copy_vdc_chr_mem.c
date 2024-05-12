/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Copy VDC character set to memory.
 */
void copyVdcChrMem(unsigned char *mem, unsigned int vdcMem, unsigned int chars) {
	unsigned char c;
	unsigned int vdcOfs = vdcMem, memOfs = 0, i;
	for (i = 0; i < chars; i++) {
		outVdc(vdcUpdAddrHi, (unsigned char) (vdcOfs >> 8));
		outVdc(vdcUpdAddrLo, (unsigned char) vdcOfs);
		// Only use 8 bytes of 16 byte character definition
		for (c = 0; c < 8; c++) {
			mem[memOfs + c] = inVdc(vdcCPUData);
		}
		memOfs += 8;
		vdcOfs += 16;
	}
}
