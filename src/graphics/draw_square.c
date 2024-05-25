/*
 * C128 CP/M bitmap square abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>

/*
 * Draw square using rectangle with aspect ratio adjustment.
 */
void drawSquare(const bitmap *bmp, const int x, const int y, const int len, const unsigned char color) {
	/* Square approximation based on aspect ratio */
	int yLen = ((len * bmp->aspectRatioMul) / bmp->aspectRatioDiv);
	drawRect(bmp, x, y, len - 1, yLen - 1, color);
}
