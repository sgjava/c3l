/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <screen.h>
#include <vic.h>

/*
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVicUpCol(uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized  */
	if (x2 - x1 + 1 == scrWidth) {
		scrollVicUpYCol(y1, y2);
	} else {
		register uchar w;
		uchar i;
		ushort destLine = (y1 * scrWidth) + x1 + (ushort) scrColMem;
		ushort sourceLine = destLine + scrWidth;
		uchar len = x2 - x1 + 1;
		for (i = y1; i < y2; i++) {
			for (w = 0; w < len; w++) {
				outp(destLine + w, inp(sourceLine + w));
			}
			destLine += scrWidth;
			sourceLine = destLine + scrWidth;
		}
	}
}
