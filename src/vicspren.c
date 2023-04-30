/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include "hitech.h"
#include "sys.h"

/*
 * Enable sprite.
 */
void enableVicSpr(uchar sprNum) {
	static uchar sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
	/* Sprite enable */
	outp(vicSprEnable, inp(vicSprEnable) | sprTable[sprNum]);
}
