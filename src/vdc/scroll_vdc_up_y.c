/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Scroll line up given y1 and y2 lines in current page.
 * copyVdcMem the entire block for speed.
 */
void scrollVdcUpY(const screen *scr, const unsigned char y1, const unsigned char y2) {
	unsigned int dispOfs = (y1 * scr->scrWidth) + (unsigned int) scr->scrMem;
	copyVdcMem(dispOfs, dispOfs - scr->scrWidth, (y2 - y1 + 1) * scr->scrWidth);
}
