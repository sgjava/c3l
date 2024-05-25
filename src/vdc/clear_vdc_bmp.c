/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Clear screen.
 */
void clearVdcBmp(const bitmap *bmp, const unsigned char c) {
	fillVdcMem(bmp->bmpMem, bmp->bmpSize, c);
}
