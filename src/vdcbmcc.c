/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Clear bitmap color memory.
 */
void clearVdcBmpCol(screen *scr, uchar c) {
	fillVdcMem(scr->bmpColMem, scr->bmpColSize, c);
}
