/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>
#include <vdc.h>

/*
 * Clear screen.
 */
void clearVdcBmp(bitmap *bmp, uchar c) {
	fillVdcMem(bmp->bmpMem, bmp->bmpSize, c);
}
