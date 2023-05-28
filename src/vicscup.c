/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vic.h>

/*
 * Scroll line up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVicUp(screen *scr, uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized  */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVicUpY(scr, y1, y2);
	} else {
		ushort scrOfs = (y1 * scr->scrWidth) + (ushort) scr->scrMem + x1;
		uchar len = x2 - x1 + 1;
		uchar lines = y2 - y1;
		scrollVicUpAsm(scrOfs, len, lines);
	}
}
