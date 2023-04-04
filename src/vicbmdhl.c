/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <graphics.h>
#include <screen.h>

/*
 * Optimized horizontal line algorithm up to 15x faster than Bresenham.
 */
void drawVicLineH(ushort x, ushort y, ushort len, uchar setPix) {
	static uchar fillTable[7] = { 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01 };
    ushort pixByte = scrWidth * (y & 0xf8) + (x & 0x1f8) + (y & 0x07);
    uchar firstBits = x % 8;
    uchar lastBits = (x + len - 1) % 8;
    ushort fillBytes = (len - lastBits - 1) >> 3;
    uchar fillByte;
    ushort i;
    if (firstBits > 0) {
        /* Handle left over bits on first byte */
        if (setPix) {
            bmpMem[pixByte] = bmpMem[pixByte] | fillTable[firstBits - 1];
        } else {
            bmpMem[pixByte] = bmpMem[pixByte] & ~fillTable[firstBits - 1];
        }
        pixByte += 8;
    }
	/* Do this outside loop */
    if (setPix) {
    	fillByte = 0xff;
    } else {
    	fillByte = 0x00;
    }
    /* Fill in bytes */
    for (i = 0; i < fillBytes; i++) {
    	bmpMem[pixByte] = fillByte;
        pixByte += 8;
    }
    /* Handle left over bits on last byte */
    if (lastBits > 0) {
        if (setPix) {
            bmpMem[pixByte] = bmpMem[pixByte] | ~fillTable[lastBits - 1];
        } else {
            bmpMem[pixByte] = bmpMem[pixByte] & fillTable[lastBits - 1];
        }
    }
}