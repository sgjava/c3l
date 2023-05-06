/*
 * C128 CP/M bitmap rectangle abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "screen.h"
#include "hitech.h"

/*
 * Draw rectangle using line drawing.
 */
void drawRect(screen *scr, int x0, int y0, int x1, int y1, uchar color) {
	/* Top */
	drawLine(scr, x0, y0, x1, y0, color);
	/* Left */
	drawLine(scr, x0, y0, x0, y1, color);
	/* Right */
	drawLine(scr, x1, y0, x1, y1, color);
	/* Bottom */
	drawLine(scr, x0, y1, x1, y1, color);
}
