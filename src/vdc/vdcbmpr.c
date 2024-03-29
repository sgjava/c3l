/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>
#include <string.h>
#include <vdc.h>

/*
 * Print without color. Optimized by setting VDC address once for each scan line.
 */
void printVdcBmp(bitmap *bmp, uchar x, uchar y, char *str) {
	ushort vdcMem = (ushort) bmp->bmpMem;
	ushort dispOfs = ((y * bmp->scrWidth) * 8) + vdcMem + x;
	ushort len = strlen(str);
	ushort i, chrOfs;
	uchar c;
	/* Draw 8 scan lines */
	for (c = 0; c < 8; c++) {
		outVdc(vdcUpdAddrHi, (uchar) (dispOfs >> 8));
		outVdc(vdcUpdAddrLo, (uchar) dispOfs);
		for (i = 0; i < len; i++) {
			chrOfs = (str[i] << 3) + c;
			outVdc(vdcCPUData, bmp->bmpChrMem[chrOfs]);
		}
		/* Next scan line */
		dispOfs += bmp->scrWidth;
	}
}
