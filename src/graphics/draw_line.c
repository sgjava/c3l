/*
 * C128 CP/M bitmap line abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <stdlib.h>

/*
 * Bresenham’s line algorithm. Color is 1 to set or 0 to clear pixel.
 */
void drawLine(bitmap *bmp, int x0, int y0, int x1, int y1, unsigned char color) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;
	/* Horizontal line */
	if ((bmp->drawLineH != NULL) && (y0 == y1)) {
		if (x0 < x1) {
			(bmp->drawLineH)(bmp, x0, y0, dx + 1, color);
		} else {
			(bmp->drawLineH)(bmp, x1, y1, dx + 1, color);
		}
		/* Vertical line */
	} else if ((bmp->drawLineV != NULL) && (x0 == x1)) {
		if (y0 < y1) {
			(bmp->drawLineV)(bmp, x0, y0, dy + 1, color);
		} else {
			(bmp->drawLineV)(bmp, x1, y1, dy + 1, color);
		}
	} else {
		/* Bresenham line */
		for (;;) {
			(bmp->setPixel)(bmp, x0, y0, color);
			if (x0 == x1 && y0 == y1)
				break;
			e2 = err;
			if (e2 > -dx) {
				err -= dy;
				x0 += sx;
			}
			if (e2 < dy) {
				err += dx;
				y0 += sy;
			}
		}
	}
}
