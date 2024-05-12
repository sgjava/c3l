/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

/*
 * Set sprite location.
 */
void setVicSprLoc(unsigned char sprNum, unsigned int x, unsigned char y) {
	static unsigned char sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	unsigned int num = sprNum << 1;
	/* Set sprite X */
	if (x > 255) {
		outp(vicSprXmsb, inp(vicSprXmsb) | sprTable[sprNum]);
		outp(vicSpr0X + num, x - 256);
	} else {
		outp(vicSprXmsb, inp(vicSprXmsb) & ~sprTable[sprNum]);
		outp(vicSpr0X + num, x);
	}
	/* Sprite Y */
	outp(vicSpr0y + num, y);
}
