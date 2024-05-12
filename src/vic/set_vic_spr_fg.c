/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

/*
 * Make sprite appear in foreground.
 */
void setVicSprFg(unsigned char sprNum) {
	static unsigned char sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	/* Sprite priority */
	outp(vicSprFg, inp(vicSprFg) & ~sprTable[sprNum]);
}
