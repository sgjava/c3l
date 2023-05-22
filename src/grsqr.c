/*
 * C128 CP/M bitmap square abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <hitech.h>

/*
 * Draw square using rectangle with aspect ratio adjustment.
 */
void drawSquare(bitmap *bmp, int x, int y, int len, uchar color) {
	/* Square approximation based on 1:0.75 aspect ratio */
	int yLen = (len / bmp->aspectRatio)
			+ ((len / bmp->aspectRatio) / bmp->aspectRatio);
	drawRect(bmp, x, y, x + len - 1, y + yLen - 1, color);
}
