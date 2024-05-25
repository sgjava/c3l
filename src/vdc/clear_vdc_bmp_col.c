/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Clear bitmap color memory.
 */
void clearVdcBmpCol(const bitmap *bmp, const unsigned char c) {
	fillVdcMem(bmp->bmpColMem, bmp->bmpColSize, bmp->color[c]);
}
