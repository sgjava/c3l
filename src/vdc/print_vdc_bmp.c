/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <string.h>
#include <vdc.h>

/*
 * Print without color. Optimized by setting VDC address once for each scan line.
 */
void printVdcBmp(bitmap *bmp, unsigned char x, unsigned char y, char *str) {
	unsigned int vdcMem = (unsigned int) bmp->bmpMem;
	unsigned int dispOfs = ((y * bmp->scrWidth) * 8) + vdcMem + x;
	unsigned int len = strlen(str);
	unsigned int i, chrOfs;
	unsigned char c;
	/* Draw 8 scan lines */
	for (c = 0; c < 8; c++) {
		outVdc(vdcUpdAddrHi, (unsigned char) (dispOfs >> 8));
		outVdc(vdcUpdAddrLo, (unsigned char) dispOfs);
		for (i = 0; i < len; i++) {
			chrOfs = (str[i] << 3) + c;
			outVdc(vdcCPUData, bmp->bmpChrMem[chrOfs]);
		}
		/* Next scan line */
		dispOfs += bmp->scrWidth;
	}
}
