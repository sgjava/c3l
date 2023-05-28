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
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVicUpCol(screen *scr, uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized function */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVicUpYCol(scr, y1, y2);
	} else {
		ushort colOfs = (y1 * scr->scrWidth) + (ushort) scr->scrColMem + x1;
		uchar len = x2 - x1 + 1;
		uchar lines = y2 - y1;
		scrollVicUp(scr, x1, y1, x2, y2);
		scrollVicUpColAsm(colOfs, len, lines);
	}
}
