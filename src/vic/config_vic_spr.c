/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <stdlib.h>
#include <vic.h>

/*
 * Configure sprite.
 */
void configVicSpr(screen *scr, unsigned char *spr, unsigned char sprNum, unsigned char sprCol) {
	unsigned char vicBank = (unsigned int) scr->scrMem / 16384;
	/* Set sprite memory location */
	scr->scrMem[vicSprMemOfs + sprNum] = ((unsigned int) spr - (vicBank * 16384))
			/ 64;
	/* Sprite color */
	outp(vicSpr0Col + sprNum, sprCol);
}
