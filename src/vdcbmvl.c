/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vdc.h"
#include "hitech.h"

/*
 * Optimized vertical line algorithm uses less calculation and flow control than drawLine.
 */
void drawVdcLineV(screen *scr, ushort x, ushort y, ushort len, uchar color) {
	uchar i, end = y+len;
	/* Plot pixels */
	for (i = y; i < end; i++) {
		setVdcPix(scr, x, i, color);
	}
}
