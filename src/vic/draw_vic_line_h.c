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
    // Precomputed masks for bit manipulation
    static const unsigned char fillTable[8] = { 0x00, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01 };
    // Calculate the starting byte position in the bitmap memory
    unsigned int pixByte = bmp->scrWidth * (y & 0xf8) + (x & 0x1f8) + (y & 0x07);
    // Calculate the number of bits to fill in the first and last byte
    unsigned char firstBits = x % 8;
    unsigned char lastBits = (x + len) % 8;
    // Number of full bytes to fill
    unsigned int fillBytes;
    unsigned int i;
    // Determine the fill byte based on the color (0xFF for white, 0x00 for black)
    unsigned char fillByte = color ? 0xff : 0x00;
    // Handle the first byte if it starts mid-byte
    if (firstBits > 0) {
        unsigned char mask = fillTable[firstBits];
        // Set or clear the bits according to the color
        bmp->bmpMem[pixByte] = color ? (bmp->bmpMem[pixByte] | mask) : (bmp->bmpMem[pixByte] & ~mask);
        pixByte += 8; // Move to the next byte
        len -= 8 - firstBits; // Adjust the length to account for the handled bits
    }
    // Calculate the number of full bytes to fill
    fillBytes = len >> 3;
    // Fill the full bytes with the fill byte
    for (i = 0; i < fillBytes; i++) {
        bmp->bmpMem[pixByte] = fillByte;
        pixByte += 8; // Move to the next byte
    }
    // Handle the last byte if it ends mid-byte
    if (lastBits > 0) {
        unsigned char mask = ~fillTable[lastBits];
        // Set or clear the bits according to the color
        bmp->bmpMem[pixByte] = color ? (bmp->bmpMem[pixByte] | mask) : (bmp->bmpMem[pixByte] & mask);
    }
}
