/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <sys.h>
#include <vic.h>

/*
 * Scroll line color up given y1 and y2 lines in current page.
 */
void scrollVicUpYCol(screen *scr, uchar y1, uchar y2) {
	/* This is the destination color address */
	ushort colOfs = y1 * scr->scrWidth + (ushort) scr->scrColMem;
	uchar lines = y2 - y1 + 1;
	scrollVicUpY(scr, y1, y2);
	scrollVicUpColAsm(colOfs, scr->scrWidth, lines);
}
