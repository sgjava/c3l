/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vic.h>

/*
 * Set pixel.
 */
void setVicPixMc(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned char color) {
    // Precompute often used values
    unsigned char pixelIndex = (x & 3) * 2;
    unsigned char charX = x >> 2;  // x / 4
    unsigned char charY = y >> 3;  // y / 8
    unsigned int charIndex = (charY * 40) + charX;
    unsigned int bitmapByteAddr = (charIndex << 3) + (y & 7);  // (charIndex * 8) + (y % 8)

    // Update the bitmap memory
    unsigned char mask = 3 << (6 - pixelIndex);
    unsigned char pixelValue = color << (6 - pixelIndex);

    bmp->bmpMem[bitmapByteAddr] = (bmp->bmpMem[bitmapByteAddr] & ~mask) | pixelValue;
}
