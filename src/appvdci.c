/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Configure screen struct for VDC and clear screen.
 */
void initVdcScr(screen *scr, ushort scrMem, ushort chrMem, uchar bgCol, uchar fgCol, uchar chrCol) {
	saveVdc();
	/* VDC Screen configuration */
	scr->scrWidth = 80;
	scr->scrHeight = 25;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	scr->chrMem = (uchar*) chrMem;
	scr->scrMem = (uchar*) scrMem;
	scr->scrColMem = (uchar*) vdcColMem;
	scr->clearScr = clearVdcScr;
	scr->clearScrCol = clearVdcScrCol;
	scr->print = printVdc;
	scr->printCol = printVdcCol;
	scr->scrollUp = scrollVdcUp;
	scr->scrollUpCol = scrollVdcUpCol;
	scr->fillMem = fillVdcMem;
	saveVdc();
	setVdcCursor(0, 0, vdcCurNone);
	(scr->clearScrCol)(scr, chrCol);
	(scr->clearScr)(scr, 32);
	setVdcFgBg(fgCol, bgCol);
}
