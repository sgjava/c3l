/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <screen.h>

/*
 * Scroll line up given y1 and y2 lines.
 */
void scrollVicUpY(screen *scr, unsigned char y1, unsigned char y2) {
	unsigned int scrOfs = y1 * scr->scrWidth + (unsigned int) scr->scrMem;
	unsigned char lines = y2 - y1;
	scrollVicUpAsm(scrOfs, scr->scrWidth, lines);
}
