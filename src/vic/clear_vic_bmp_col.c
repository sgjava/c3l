/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vic.h>

/*
 * Clear bitmap color memory.
 */
void clearVicBmpCol(const bitmap *bmp, const unsigned char c) {
	fillVicMem(bmp->bmpColMem, bmp->bmpColSize, c);
}
