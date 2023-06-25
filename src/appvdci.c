/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Configure screen struct for VDC.
 */
void initVdcScr(screen *scr, ushort scrMem, ushort chrMem) {
	static uchar vdcColors[16] = { vdcBlack, vdcWhite, vdcDarkRed, vdcLightCyan,
	vdcLightPurple, vdcDarkGreen, vdcDarkBlue, vdcLightYellow,
	vdcDarkPurple, vdcDarkYellow, vdcLightRed, vdcDarkCyan, vdcDarkGray,
	vdcLightGreen, vdcLightBlue, vdcMedGray };
	/* Map colors */
	uchar i, len = sizeof(vdcColors);
	for (i = 0; i < len; i++) {
		scr->color[i] = vdcAltChrSet | vdcColors[i];
	}
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
	scr->copyScrToStr = copyVdcToStr;
}
