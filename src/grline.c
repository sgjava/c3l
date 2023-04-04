/*
 * C128 CP/M bitmap line abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <graphics.h>
#include "hitech.h"
#include "sys.h"

/*
 * Bresenham’s line algorithm. setPix is 1 to set or 0 to clear pixel.
 */
void drawLine(int x0, int y0, int x1, int y1, uchar setPix) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;
    /* Horizontal line */
    if ((drawLineH != NULL) && (y0 == y1)) {
        if (x0 < x1) {
            (*drawLineH)(x0, y0, dx + 1, setPix);
        } else {
            (*drawLineH)(x1, y1, dx + 1, setPix);
        }
        /* Vertical line */
    } else if ((drawLineV != NULL) && (x0 == x1)) {
        if (y0 < y1) {
            (*drawLineV)(x0, y0, dy + 1, setPix);
        } else {
            (*drawLineV)(x1, y1, dy + 1, setPix);
        }
    } else {
        /* Bresenham line */
    	void (*drawPix)(ushort, ushort);
    	/* Do this outside loop */
        if (setPix) {
        	drawPix = setPixel;
        } else {
        	drawPix = clearPixel;
        }
        for (;;) {
        	(*drawPix)(x0, y0);
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
