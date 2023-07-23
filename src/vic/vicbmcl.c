/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>
#include <vic.h>

/*
 * Clear screen uchar.
 */
void clearVicBmp(bitmap *bmp, uchar c) {
	fillVicMem(bmp->bmpMem, bmp->bmpSize, c);
}
