/*
 * C128 CP/M bitmap circle abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "screen.h"
#include "hitech.h"

/*
 * Draw circle using ellipse with aspect ratio adjustment.
 */
void drawCircle(screen *scr, int xc, int yc, int a, uchar color) {
	/* Circle approximation based on 1:0.75 aspect ratio */
	drawEllipse(scr, xc, yc, a,
			(a / scr->aspectRatio)
					+ ((a / scr->aspectRatio) / scr->aspectRatio), color);
}
