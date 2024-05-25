/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>

/*
 * Scroll line color up given y1 and y2 lines in current page.
 */
void scrollVicUpYCol(const screen *scr, const unsigned char y1, const unsigned char y2) {
	/* This is the destination color address */
	unsigned int colOfs = y1 * scr->scrWidth + (unsigned int) scr->scrColMem;
	unsigned char lines = y2 - y1;
	scrollVicUpY(scr, y1, y2);
	scrollVicUpColAsm(colOfs, scr->scrWidth, lines);
}
