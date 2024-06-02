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
	unsigned char charX = x / 4;
	unsigned char charY = y / 8;
	unsigned int charIndex = charY * 40 + charX;
	unsigned int bitmapByteAddr = (charIndex * 8) + (y % 8);
	unsigned int pixelIndex = (x % 4) * 2;
	// Update the bitmap memory
	bmp->bmpMem[bitmapByteAddr] &= ~(3 << (6 - pixelIndex)); // Clear the bits
	bmp->bmpMem[bitmapByteAddr] |= (color << (6 - pixelIndex)); // Set the color bits
}
