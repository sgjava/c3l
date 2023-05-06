/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vic.h"
#include "hitech.h"
#include <sys.h>

/*
 * Set sprite location.
 */
void setVicSprLoc(uchar sprNum, ushort x, uchar y) {
	static uchar sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	register ushort num = sprNum << 1;
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
