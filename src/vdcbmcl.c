/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <vdc.h>
#include <graphics.h>

/*
 * Clear screen.
 */
void clearVdcBmp(uchar c) {
    fillVdcMem((ushort) bmpMem, bmpSize, c);
}
