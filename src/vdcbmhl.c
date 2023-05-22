/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>
#include <vdc.h>

/*
 * Optimized horizontal line algorithm up to 40x faster than Bresenham.
 */
void drawVdcLineH(bitmap *bmp, ushort x, ushort y, ushort len, uchar color) {
	static uchar fillTable[7] = { 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01 };
	ushort vdcMem = (ushort) bmp->bmpMem;
	ushort pixByte = vdcMem + (y << 6) + (y << 4) + (x >> 3);
	uchar firstBits = x % 8;
	uchar lastBits = (x + len - 1) % 8;
	ushort fillBytes = (len - lastBits - 1) >> 3;
	uchar fillByte;
	ushort i;
	if (firstBits > 0) {
		/* Handle left over bits on first byte */
		if (color) {
			orVdcByte(pixByte, fillTable[firstBits - 1]);
		} else {
			andVdcByte(pixByte, ~fillTable[firstBits - 1]);
		}
		pixByte += 1;
	} else {
		outVdc(vdcUpdAddrHi, (uchar) (pixByte >> 8));
		outVdc(vdcUpdAddrLo, (uchar) pixByte);
	}
	/* Do this outside loop */
	if (color) {
		fillByte = 0xff;
	} else {
		fillByte = 0x00;
	}
	/* Fill in bytes */
	for (i = 0; i < fillBytes; i++) {
		outVdc(vdcCPUData, fillByte);
	}
	pixByte += fillBytes;
	/* Handle left over bits on last byte */
	if (lastBits > 0) {
		if (color) {
			orVdcByte(pixByte, ~fillTable[lastBits - 1]);
		} else {
			andVdcByte(pixByte, fillTable[lastBits - 1]);
		}
	}
}
