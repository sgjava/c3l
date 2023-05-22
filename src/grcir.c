/*
 * C128 CP/M bitmap circle abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <hitech.h>

/*
 * Draw circle using ellipse with aspect ratio adjustment.
 */
void drawCircle(bitmap *bmp, int xc, int yc, int a, uchar color) {
	/* Circle approximation based on 1:0.75 aspect ratio */
	drawEllipse(bmp, xc, yc, a,
			(a / bmp->aspectRatio)
					+ ((a / bmp->aspectRatio) / bmp->aspectRatio), color);
}
