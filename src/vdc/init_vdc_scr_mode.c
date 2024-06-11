/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Configure for VDC mode and clear screen.
 */
void initVdcScrMode(const screen *scr, const unsigned char bgCol, const unsigned char fgCol, const unsigned char chrCol) {
	saveVdc();
	setVdcCursor(0, 0, vdcCurNone);
	setVdcDspPage(scr->scrMem, scr->scrColMem);
	(scr->clearScrCol)(scr, chrCol);
	(scr->clearScr)(scr, 32);
	setVdcFgBg(scr->color[fgCol], scr->color[bgCol]);
}
