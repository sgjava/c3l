/*
 * C128 CP/M bitmap square abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>

/*
 * Draw square using rectangle with aspect ratio adjustment.
 */
void drawSquare(screen *scr, int x, int y, int len, uchar color) {
	/* Square approximation based on 1:0.75 aspect ratio */
	int yLen = (len / scr->aspectRatio)
			+ ((len / scr->aspectRatio) / scr->aspectRatio);
	drawRect(scr, x, y, x + len - 1, y + yLen - 1, color);
}
