/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Optimized horizontal line algorithm up to 40x faster than Bresenham.
 */
void drawVdcLineH(bitmap *bmp, unsigned int x, unsigned int y, unsigned int len, unsigned char color) {
	static unsigned char fillTable[7] = { 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01 };
	unsigned int vdcMem = (unsigned int) bmp->bmpMem;
	unsigned int pixByte = vdcMem + (y << 6) + (y << 4) + (x >> 3);
	unsigned char firstBits = x % 8;
	unsigned char lastBits = (x + len) % 8;
	unsigned int fillBytes;
	unsigned char fillByte;
	unsigned int i;
	if (firstBits > 0) {
		/* Handle left over bits on first byte */
		if (color) {
			orVdcByte(pixByte, fillTable[firstBits - 1]);
		} else {
			andVdcByte(pixByte, ~fillTable[firstBits - 1]);
		}
		pixByte += 1;
	} else {
		outVdc(vdcUpdAddrHi, (unsigned char) (pixByte >> 8));
		outVdc(vdcUpdAddrLo, (unsigned char) pixByte);
	}
	/* Do this outside loop */
	if (color) {
		fillByte = 0xff;
	} else {
		fillByte = 0x00;
	}
	/* We only use byte fill if length > 7 pixels */
	if (len > 7) {
		fillBytes = (len - lastBits) >> 3;
		for (i = 0; i < fillBytes; i++) {
			outVdc(vdcCPUData, fillByte);
		}
		pixByte += fillBytes;
	}
	/* Handle left over bits on last byte */
	if (lastBits > 0) {
		if (color) {
			orVdcByte(pixByte, ~fillTable[lastBits - 1]);
		} else {
			andVdcByte(pixByte, fillTable[lastBits - 1]);
		}
	}
}
