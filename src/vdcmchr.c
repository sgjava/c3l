/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <vdc.h>

/*
 * Copy character set to VDC memory.
 */
void copyVdcMemChr(uchar *mem, ushort vdcMem, ushort chars) {
	register uchar c;
	ushort vdcOfs = vdcMem, memOfs = 0, i;
	for (i = 0; i < chars; i++) {
		outVdc(vdcUpdAddrHi, (uchar) (vdcOfs >> 8));
		outVdc(vdcUpdAddrLo, (uchar) vdcOfs);
		/* Only use 8 bytes of 16 byte character definition */
		for (c = 0; c < 8; c++) {
			outVdc(vdcCPUData, mem[memOfs + c]);
		}
		memOfs += 8;
		vdcOfs += 16;
	}
}
