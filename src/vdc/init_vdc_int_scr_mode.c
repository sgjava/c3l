/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Configure for VDC interlace mode and clear screen.
 */
void initVdcIntScrMode(const screen *scr, const unsigned char bgCol, const unsigned char fgCol, const unsigned char chrCol) {
	saveVdc();
	setVdcCursor(0, 0, vdcCurNone);
	// Set 80x50 interlaced text mode with 8x8 chars
	outVdc(vdcHzTotal, 128);
	outVdc(vdcVtTotal, 64);
	outVdc(vdcVtDisp, 50);
	outVdc(vdcVtSyncPos, 58);
	outVdc(vdcIlaceMode, 3);
	outVdc(vdcChTotalVt, 7);
	setVdcDspPage(scr->scrMem, scr->scrColMem);
	(scr->clearScrCol)(scr, chrCol);
	(scr->clearScr)(scr, 32);
	setVdcFgBg(scr->color[fgCol], scr->color[bgCol]);
}
