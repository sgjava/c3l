/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>
#include <vdc.h>

/*
 * Clear bitmap color memory.
 */
void clearVdcBmpCol(bitmap *bmp, uchar c) {
	fillVdcMem(bmp->bmpColMem, bmp->bmpColSize, c);
}
