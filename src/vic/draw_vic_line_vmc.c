/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <bitmap.h>

/*
 * Optimized vertical line algorithm uses less calculation than setVicPix.
 */
void drawVicLineVMc(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len,
		const unsigned char color) {
	// Colors 0-3 pixels
	static const unsigned char bitTable[4][4] = { { 0x3f, 0xcf, 0xf3, 0xfc }, { 0x40, 0x10, 0x04, 0x01 },
			{ 0x80, 0x20, 0x08, 0x02 }, { 0xc0, 0x30, 0x0c, 0x03 } };
	unsigned int pixByte = bmp->scrWidth * (y & 0xf8) + (x << 1 & 0x1f8) + (y & 0x07);
	unsigned char i;
	unsigned char vBit = bitTable[color][x & 0x03];
	/* Plot pixels */
	for (i = 0; i < len; i++) {
		if (color) {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] | vBit;
		} else {
			bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] & vBit;
		}
		y += 1;
		/* Increment based on char boundary */
		if ((y & 7) > 0) {
			pixByte += 1;
		} else {
			pixByte += 313;
		}
	}
}
