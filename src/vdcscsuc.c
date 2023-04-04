/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>
#include "hitech.h"

/*
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVdcUpCol(uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized  */
	if (x2 - x1 + 1 == scrWidth) {
		scrollVdcUpYCol(y1, y2);
	} else {
		uchar len = x2 - x1 + 1;
		ushort colOfs = (y1 * scrWidth) + (ushort) scrColMem + x1;
		scrollVdcUp(x1, y1, x2, y2);
		for (; y1 <= y2; y1++) {
			copyVdcMem(colOfs, colOfs - scrWidth, len);
			colOfs += scrWidth;
		}
	}
}
