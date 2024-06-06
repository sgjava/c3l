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
    static const unsigned char fillTable[4] = { 0x00, 0x55, 0xaa, 0xff };
    // Colors 0-3 left fill pixels
    static const unsigned char leftTable[4][3] = {
        { 0xc0, 0xf0, 0xfc },
        { 0x15, 0x05, 0x01 },
        { 0x2a, 0x0a, 0x02 },
        { 0x3f, 0x0f, 0x03 }
    };
    // Colors 0-3 right fill pixels
    static const unsigned char rightTable[4][3] = {
        { 0x3f, 0x0f, 0x03 },
        { 0x40, 0x50, 0x54 },
        { 0x80, 0xa0, 0xa8 },
        { 0xc0, 0xf0, 0xfc }
    };
    unsigned int pixByte = bmp->scrWidth * (y & 0xf8) + (x << 1 & 0x1f8) + (y & 0x07);
    unsigned char firstBits = x % 4;
    unsigned char lastBits = (x + len) % 4;
    unsigned int fillBytes;
    unsigned char fillByte = fillTable[color];
    unsigned int i;
    if (firstBits > 0) {
        // Handle left over bits on the first byte
        bmp->bmpMem[pixByte] |= leftTable[color][firstBits - 1];
        pixByte += 8;
        len -= (4 - firstBits);
    }
    // We only use byte fill if length > 3 pixels
    if (len > 3) {
        fillBytes = len >> 2; // Number of full bytes to fill
        for (i = 0; i < fillBytes; i++) {
            bmp->bmpMem[pixByte] = fillByte;
            pixByte += 8;
        }
    }
    // Handle left over bits on the last byte
    if (lastBits > 0) {
        bmp->bmpMem[pixByte] |= rightTable[color][lastBits - 1];
    }
}
