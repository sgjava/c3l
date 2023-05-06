/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Clear screen.
 */
void clearVdcBmp(screen *scr, uchar c) {
	fillVdcMem(scr->bmpMem, scr->bmpSize, c);
}
