/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include "hitech.h"
#include "sys.h"

/*
 * Configure sprite.
 */
void configVicSpr(screen *scr, uchar *spr, uchar sprNum, uchar sprCol) {
	uchar vicBank = (ushort) scr->scrMem / 16384;
	/* Set sprite memory location */
	scr->scrMem[vicSprMemOfs + sprNum] = ((ushort) spr - (vicBank * 16384)) / 64;
	/* Sprite color */
	outp(vicSpr0Col + sprNum, sprCol);
}
