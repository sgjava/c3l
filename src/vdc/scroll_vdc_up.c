/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Scroll line up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVdcUp(screen *scr, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	/* If line is screen width use optimized function */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVdcUpY(scr, y1, y2);
	} else {
		unsigned char len = x2 - x1 + 1;
		unsigned int dispOfs = (y1 * scr->scrWidth) + (unsigned int) scr->scrMem + x1;
		for (; y1 <= y2; y1++) {
			copyVdcMem(dispOfs, dispOfs - scr->scrWidth, len);
			dispOfs += scr->scrWidth;
		}
	}
}
