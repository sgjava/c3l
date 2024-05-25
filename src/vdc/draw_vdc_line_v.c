/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Optimized vertical line algorithm uses less calculation and flow control than drawLine.
 */
void drawVdcLineV(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len, const unsigned char color) {
	unsigned char i, end = y + len;
	/* Plot pixels */
	for (i = y; i < end; i++) {
		setVdcPix(bmp, x, i, color);
	}
}
