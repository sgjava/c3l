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
void drawRect(bitmap *bmp, int x, int y, int w, int h, uchar color) {
	/* Top */
	drawLine(bmp, x, y, x + w - 1, y, color);
	/* Left */
	drawLine(bmp, x, y + 1, x, y + h - 1, color);
	/* Right */
	drawLine(bmp, x + w -1, y + 1, x + w - 1, y + h - 1, color);
	/* Bottom */
	drawLine(bmp, x, y + h - 1, x + w - 1, y + h - 1, color);
}
