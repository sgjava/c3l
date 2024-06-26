/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Clear screen color.
 */
void clearVdcScrCol(const screen *scr, const unsigned char c) {
	fillVdcMem(scr->scrColMem, scr->scrSize, scr->color[c]);
}
