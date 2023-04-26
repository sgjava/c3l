/*
 * C128 CP/M bitmap line abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <screen.h>
#include "hitech.h"
#include "sys.h"

/*
 * Bresenham’s line algorithm. Color is 1 to set or 0 to clear pixel.
 */
void drawLine(screen *scr, int x0, int y0, int x1, int y1, uchar color) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;
	/* Horizontal line */
	if ((scr->drawLineH != NULL) && (y0 == y1)) {
		if (x0 < x1) {
			(scr->drawLineH)(scr, x0, y0, dx + 1, color);
		} else {
			(scr->drawLineH)(scr, x1, y1, dx + 1, color);
		}
		/* Vertical line */
	} else if ((scr->drawLineV != NULL) && (x0 == x1)) {
		if (y0 < y1) {
			(scr->drawLineV)(scr, x0, y0, dy + 1, color);
		} else {
			(scr->drawLineV)(scr, x1, y1, dy + 1, color);
		}
	} else {
		/* Bresenham line */
		for (;;) {
			(scr->setPixel)(scr, x0, y0, color);
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
