/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

/*
 * Enable sprite.
 */
void enableVicSpr(const unsigned char sprNum) {
	static unsigned char sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	/* Sprite enable */
	outp(vicSprEnable, inp(vicSprEnable) | sprTable[sprNum]);
}
