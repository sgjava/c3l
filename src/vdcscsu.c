/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Scroll line up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVdcUp(uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized  */
	if (x2 - x1 + 1 == scrWidth) {
		scrollVdcUpY(y1, y2);
	} else {
		uchar len = x2 - x1 + 1;
		ushort dispOfs = (y1 * 80) + (ushort) scrMem + x1;
		for (; y1 <= y2; y1++) {
			copyVdcMem(dispOfs, dispOfs - scrWidth, len);
			dispOfs += scrWidth;
		}
	}
}
