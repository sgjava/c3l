/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <stdlib.h>
#include <vic.h>

/*
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVicUpCol(const screen *scr, const unsigned char x1, const unsigned char y1, const unsigned char x2,
		const unsigned char y2) {
	/* If line is screen width use optimized function */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVicUpYCol(scr, y1, y2);
	} else {
		unsigned int colOfs = (y1 * scr->scrWidth) + (unsigned int) scr->scrColMem + x1;
		unsigned char len = x2 - x1 + 1;
		unsigned char lines = y2 - y1;
		scrollVicUp(scr, x1, y1, x2, y2);
		scrollVicUpColAsm(colOfs, len, lines);
	}
}
