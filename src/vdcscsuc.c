/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"

/*
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVdcUpCol(screen *scr, uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized function */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVdcUpYCol(scr, y1, y2);
	} else {
		uchar len = x2 - x1 + 1;
		ushort colOfs = (y1 * scr->scrWidth) + (ushort) scr->scrColMem + x1;
		scrollVdcUp(scr, x1, y1, x2, y2);
		for (; y1 <= y2; y1++) {
			copyVdcMem(colOfs, colOfs - scr->scrWidth, len);
			colOfs += scr->scrWidth;
		}
	}
}
