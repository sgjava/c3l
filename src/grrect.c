/*
 * C128 CP/M bitmap line abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <graphics.h>
#include "hitech.h"

/*
 * Draw rectangle using line drawing.
 */
void drawRect(int x0, int y0, int x1, int y1, uchar setPix) {
    /* Top */
    drawLine(x0, y0, x1, y0, setPix);
    /* Left */
    drawLine(x0, y0, x0, y1, setPix);
    /* Right */
    drawLine(x1, y0, x1, y1, setPix);
    /* Bottom */
    drawLine(x0, y1, x1, y1, setPix);
}
