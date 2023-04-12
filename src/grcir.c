/*
 * C128 CP/M bitmap ellipse abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <graphics.h>
#include "hitech.h"

/*
 * Draw circle using ellipse with aspect ratio adjustment.
 */
void drawCircle(int xc, int yc, int a, uchar color) {
    /* Circle approximation based on 1:0.75 aspect ratio */
    drawEllipse(xc, yc, a,
            (a / aspectRatio) + ((a / aspectRatio) / aspectRatio), color);
}
