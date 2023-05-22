/*
 * C128 CP/M bitmap rectangle abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <hitech.h>

/*
 * Draw rectangle using line drawing.
 */
void drawRect(bitmap *bmp, int x0, int y0, int x1, int y1, uchar color) {
	/* Top */
	drawLine(bmp, x0, y0, x1, y0, color);
	/* Left */
	drawLine(bmp, x0, y0, x0, y1, color);
	/* Right */
	drawLine(bmp, x1, y0, x1, y1, color);
	/* Bottom */
	drawLine(bmp, x0, y1, x1, y1, color);
}
