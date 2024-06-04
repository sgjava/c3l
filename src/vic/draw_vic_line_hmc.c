/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <bitmap.h>

/*
 * Optimized horizontal line algorithm for multi-color mode.
 */
void drawVicLineHMc(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len,
		const unsigned char color) {
	// Colors 0-3 fill table
	static unsigned char fillTable[4] = { 0x00, 0x55, 0xaa, 0xff };
	// Colors 0-3 left fill pixels
	static unsigned char leftTable[4][3] =
			{ { 0xc0, 0xf0, 0xfc }, { 0x15, 0x05, 0x01 }, { 0x2a, 0x0a, 0x02 }, { 0x3f, 0x0f, 0x03 } };
	// Colors 0-3 right fill pixels
	static unsigned char rightTable[4][3] =
			{ { 0x3f, 0x0f, 0x03 }, { 0x40, 0x50, 0x54 }, { 0x80, 0xa0, 0xa8 }, { 0xc0, 0xf0, 0xfc } };
	unsigned int pixByte = bmp->scrWidth * (y & 0xf8) + (x & 0x1f8) + (y & 0x07);
	unsigned char firstBits = x % 4;
	unsigned char lastBits = (x + len) % 4;
	unsigned int fillBytes;
	unsigned char fillByte;
	unsigned int i;
	if (firstBits > 0) {
		/* Handle left over bits on first byte */
		if (color) {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] | leftTable[color][firstBits - 1];
		} else {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] & leftTable[color][firstBits - 1];
		}
		pixByte += 8;
	}
	/* Do this outside loop */
	fillByte = fillTable[color];
	/* We only use byte fill if length > 3 pixels */
	if (len > 3) {
		fillBytes = (len - lastBits) >> 2;
		/* Fill in bytes */
		for (i = 0; i < fillBytes; i++) {
			bmp->bmpMem[pixByte] = fillByte;
			pixByte += 8;
		}
	}
	/* Handle left over bits on last byte */
	if (lastBits > 0) {
		if (color) {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] | rightTable[color][lastBits - 1];
		} else {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] & rightTable[color][lastBits - 1];
		}
	}
}
