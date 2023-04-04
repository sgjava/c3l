/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"
#include "sys.h"

/*
 * Copy VDC character set to memory.
 */
void copyVdcChrMem(uchar *mem, ushort vdcMem, ushort chars) {
	register uchar c;
	ushort vdcOfs = vdcMem, memOfs = 0, i;
	for (i = 0; i < chars; i++) {
		outVdc(vdcUpdAddrHi, (uchar) (vdcOfs >> 8));
		outVdc(vdcUpdAddrLo, (uchar) vdcOfs);
		/* Only use 8 bytes of 16 byte character definition */
		for (c = 0; c < 8; c++) {
			mem[memOfs + c] = inVdc(vdcCPUData);
		}
		memOfs += 8;
		vdcOfs += 16;
	}
}
