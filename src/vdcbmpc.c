/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <string.h>
#include "vdc.h"
#include "hitech.h"

/*
 * Print with color. Optimized by setting VDC address once for each scan line.
 * Right now this is for 640x200 mode which doesn't support color.
 */
void printVdcBmpCol(screen *scr, uchar x, uchar y, uchar color, char *str) {
	ushort vdcMem = (ushort) scr->bmpMem;
	ushort dispOfs = ((y * scr->scrWidth) * 8) + vdcMem + x;
	ushort len = strlen(str);
	ushort i, chrOfs;
	uchar c;
	/* Draw 8 scan lines */
	for (c = 0; c < 8; c++) {
		outVdc(vdcUpdAddrHi, (uchar) (dispOfs >> 8));
		outVdc(vdcUpdAddrLo, (uchar) dispOfs);
		for (i = 0; i < len; i++) {
			chrOfs = (str[i] << 3) + c;
			outVdc(vdcCPUData, scr->bmpChrMem[chrOfs]);
		}
		/* Next scan line */
		dispOfs += scr->scrWidth;
	}
}
