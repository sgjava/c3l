/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>

/*
 * Set pixel.
 */
void setVicPix(bitmap *bmp, ushort x, ushort y, uchar color) {
	static uchar setBitTable[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
	static uchar clearBitTable[8] = { 127, 191, 223, 239, 247, 251, 253, 254 };
	ushort pixByte = bmp->scrWidth * (y & 0xf8) + (x & 0x1f8) + (y & 0x07);
	if (color) {
		bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] | (setBitTable[x & 0x07]);
	} else {
		bmp->bmpMem[pixByte] = bmp->bmpMem[pixByte] & (clearBitTable[x & 0x07]);
	}
}
