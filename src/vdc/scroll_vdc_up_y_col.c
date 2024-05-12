/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Scroll line color up given y1 and y2 lines in current page.
 * copyVdcMem the entire block for speed.
 */
void scrollVdcUpYCol(screen *scr, unsigned char y1, unsigned char y2) {
	unsigned int colOfs = (y1 * scr->scrWidth) + (unsigned int) scr->scrColMem;
	scrollVdcUpY(scr, y1, y2);
	copyVdcMem(colOfs, colOfs - scr->scrWidth, (y2 - y1 + 1) * scr->scrWidth);
}
