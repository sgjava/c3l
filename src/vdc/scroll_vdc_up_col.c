/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVdcUpCol(const screen *scr, const unsigned char x1, const unsigned char y1, const unsigned char x2,
		const unsigned char y2) {
	/* If line is screen width use optimized function */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVdcUpYCol(scr, y1, y2);
	} else {
		unsigned char len = x2 - x1 + 1;
		unsigned int colOfs = (y1 * scr->scrWidth) + (unsigned int) scr->scrColMem + x1;
		scrollVdcUp(scr, x1, y1, x2, y2);
		for (; y1 <= y2; y1++) {
			copyVdcMem(colOfs, colOfs - scr->scrWidth, len);
			colOfs += scr->scrWidth;
		}
	}
}
