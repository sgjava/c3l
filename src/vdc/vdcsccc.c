/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Clear screen color.
 */
void clearVdcScrCol(screen *scr, uchar c) {
	fillVdcMem(scr->scrColMem, scr->scrSize, scr->color[c]);
}
