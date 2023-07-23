/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>

/*
 * Scroll line up given y1 and y2 lines.
 */
void scrollVicUpY(screen *scr, uchar y1, uchar y2) {
	ushort scrOfs = y1 * scr->scrWidth + (ushort) scr->scrMem;
	uchar lines = y2 - y1;
	scrollVicUpAsm(scrOfs, scr->scrWidth, lines);
}
