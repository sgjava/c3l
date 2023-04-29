/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include "hitech.h"
#include "sys.h"

/*
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVicUpCol(screen *scr, uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized function */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVicUpYCol(scr, y1, y2);
	} else {
		register uchar w;
		uchar i;
		ushort destLine = (y1 * scr->scrWidth) + x1 + (ushort) scr->scrColMem;
		ushort sourceLine = destLine + scr->scrWidth;
		uchar len = x2 - x1 + 1;
		scrollVicUp(scr, x1, y1, x2, y2);
		for (i = y1; i < y2; i++) {
			for (w = 0; w < len; w++) {
				outp(destLine + w, inp(sourceLine + w));
			}
			destLine += scr->scrWidth;
			sourceLine = destLine + scr->scrWidth;
		}
	}
}
