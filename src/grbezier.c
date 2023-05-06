/*
 * C128 CP/M bitmap Bézier curve abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <stdlib.h>

/*
 * Bézier curve using Bresenham’s line algorithm.
 */
void drawBezier(screen *scr, int x0, int y0, int x1, int y1, int x2, int y2,
uchar color) {
	int sx = x0 < x2 ? 1 : -1;
	int sy = y0 < y2 ? 1 : -1;
	int x = x2 - x0;
	int y = y2 - y0;
	int dx = abs(x);
	int dy = abs(y);
	int ex = dx << 1;
	int ey = dy << 1;
	int err = ex - ey;
	int cx = x0;
	int cy = y0;
	int e2;
	for (;;) {
		(scr->setPixel)(scr, cx, cy, color);
		if (cx == x2 && cy == y2) {
			break;
		}
		e2 = err << 1;
		if (e2 > -ey) {
			err -= ey;
			cx += sx;
		}
		if (e2 < ex) {
			err += ex;
			cy += sy;
		}
	}
}
