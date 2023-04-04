/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>
#include "hitech.h"

/*
 * Scroll line color up given y1 and y2 lines in current page.
 */
void scrollVicUpYCol(uchar y1, uchar y2) {
	ushort i;
	ushort dest = y1 * scrWidth + (ushort) scrColMem;
	ushort source = dest + scrWidth;
	ushort len = (y2 - y1) * scrWidth;
	scrollVicUpY(y1, y2);
	for (i = 0; i < len; i++) {
		outp(dest + i, inp(source + i));
	}
}
