/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vic.h"
#include "hitech.h"

/*
 * Scroll line color up given y1 and y2 lines in current page.
 */
void scrollVicUpYCol(screen *scr, uchar y1, uchar y2) {
	ushort i;
	ushort dest = y1 * scr->scrWidth + (ushort) scr->scrColMem;
	ushort source = dest + scr->scrWidth;
	ushort len = (y2 - y1) * scr->scrWidth;
	scrollVicUpY(scr, y1, y2);
	for (i = 0; i < len; i++) {
		outp(dest + i, inp(source + i));
	}
}
