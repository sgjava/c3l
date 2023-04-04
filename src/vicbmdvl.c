/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <graphics.h>
#include <screen.h>

/*
 * Optimized vertical line algorithm uses less calculation than setVicPix.
 */
void drawVicLineV(ushort x, ushort y, ushort len, uchar setPix) {
	static uchar bitTable[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    ushort pixByte = scrWidth * (y & 0xf8) + (x & 0x1f8) + (y & 0x07);
    uchar vBit = bitTable[x & 0x07];
    uchar i;
    /* Plot pixels */
    for (i = 0; i < len; i++) {
        if (setPix) {
            bmpMem[pixByte] = bmpMem[pixByte] | vBit;
        } else {
            bmpMem[pixByte] = bmpMem[pixByte] & ~vBit;
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
