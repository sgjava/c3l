/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <vdc.h>
#include <graphics.h>

/*
 * Clear bitmap color memory.
 */
void clearVdcBmpCol(uchar c) {
    fillVdcMem((ushort) bmpColMem, bmpColSize, c);
}