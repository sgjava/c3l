/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <bitmap.h>

/*
 * Optimized horizontal line algorithm up to 15x faster than Bresenham.
 */
void drawVicLineH(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len, const unsigned char color) {
	static unsigned char fillTable[7] = { 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01 };
	unsigned int pixByte = bmp->scrWidth * (y & 0xf8) + (x & 0x1f8) + (y & 0x07);
	unsigned char firstBits = x % 8;
	unsigned char lastBits = (x + len) % 8;
	unsigned int fillBytes;
	unsigned char fillByte;
	unsigned int i;
	if (firstBits > 0) {
		/* Handle left over bits on first byte */
		if (color) {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte]
					| fillTable[firstBits - 1];
		} else {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte]
					& ~fillTable[firstBits - 1];
		}
		pixByte += 8;
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
		/* Fill in bytes */
		for (i = 0; i < fillBytes; i++) {
			bmp->bmpMem[pixByte] = fillByte;
			pixByte += 8;
		}
	}
	/* Handle left over bits on last byte */
	if (lastBits > 0) {
		if (color) {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte]
					| ~fillTable[lastBits - 1];
		} else {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte]
					& fillTable[lastBits - 1];
		}
	}
}
