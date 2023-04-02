/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Scroll line up given y1 and y2 lines in current page.
 * copyVdcMem the entire block for speed.
 */
void scrollVdcUpY(uchar y1, uchar y2) {
	ushort dispOfs = (y1 * scrWidth) + (ushort) scrMem;
	copyVdcMem(dispOfs, dispOfs - scrWidth, (y2 - y1 + 1) * scrWidth);
}
