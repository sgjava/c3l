/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <graphics.h>
#include <screen.h>

/*
 * Set pixel.
 */
void setVicPix(ushort x, ushort y) {
	static uchar bitTable[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    ushort pixByte = scrWidth * (y & 0xf8) + (x & 0x1f8) + (y & 0x07);
    bmpMem[pixByte] = bmpMem[pixByte] | (bitTable[x & 0x07]);
}
