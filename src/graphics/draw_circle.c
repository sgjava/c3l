/*
 * C128 CP/M bitmap circle abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>

/*
 * Draw circle using ellipse with aspect ratio adjustment.
 */
void drawCircle(bitmap *bmp, int xc, int yc, int a, unsigned char color) {
	/* Circle approximation based on aspect ratio */
	int b = ((a * bmp->aspectRatioMul) / bmp->aspectRatioDiv);
	drawEllipse(bmp, xc, yc, a, b, color);
}
