/*
 * C128 CP/M bitmap line abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <graphics.h>
#include "hitech.h"

/*
 * Draw square using rectangle with aspect ratio adjustment.
 */
void drawSquare(int x, int y, int len, uchar setPix) {
    /* Square approximation based on 1:0.75 aspect ratio */
    int yLen = (len / aspectRatio) + ((len / aspectRatio) / aspectRatio);
    drawRect(x, y, x + len - 1, y + yLen - 1, setPix);
}
