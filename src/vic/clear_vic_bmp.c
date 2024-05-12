/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vic.h>

/*
 * Clear screen unsigned char.
 */
void clearVicBmp(bitmap *bmp, unsigned char c) {
	fillVicMem(bmp->bmpMem, bmp->bmpSize, c);
}
