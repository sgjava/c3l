/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Configure screen struct for VDC and clear screen.
 */
void initVdcScrMode(screen *scr, unsigned char bgCol, unsigned char fgCol, unsigned char chrCol) {
	saveVdc();
	setVdcCursor(0, 0, vdcCurNone);
	(scr->clearScrCol)(scr, chrCol);
	(scr->clearScr)(scr, 32);
	setVdcFgBg(scr->color[fgCol], scr->color[bgCol]);
}
