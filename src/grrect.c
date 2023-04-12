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
void drawRect(int x0, int y0, int x1, int y1, uchar color) {
    /* Top */
    drawLine(x0, y0, x1, y0, color);
    /* Left */
    drawLine(x0, y0, x0, y1, color);
    /* Right */
    drawLine(x1, y0, x1, y1, color);
    /* Bottom */
    drawLine(x0, y1, x1, y1, color);
}
