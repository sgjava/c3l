/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Configure screen struct for VDC interlace mode.
 */
void initVdcIntScr(const screen *scr, const unsigned int scrMem, const unsigned int colMem, const unsigned int chrMem) {
	static unsigned char vdcColors[16] = { vdcBlack, vdcWhite, vdcDarkRed, vdcLightCyan,
	vdcLightPurple, vdcDarkGreen, vdcDarkBlue, vdcLightYellow,
	vdcDarkPurple, vdcDarkYellow, vdcLightRed, vdcDarkCyan, vdcDarkGray,
	vdcLightGreen, vdcLightBlue, vdcMedGray };
	/* Map colors */
	unsigned char i, len = sizeof(vdcColors);
	for (i = 0; i < len; i++) {
		scr->color[i] = vdcAltChrSet | vdcColors[i];
	}
	scr->scrWidth = 80;
	scr->scrHeight = 50;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	scr->chrMem = (unsigned char*) chrMem;
	scr->scrMem = (unsigned char*) scrMem;
	scr->scrColMem = (unsigned char*) colMem;
	scr->clearScr = clearVdcScr;
	scr->clearScrCol = clearVdcScrCol;
	scr->print = printVdc;
	scr->printCol = printVdcCol;
	scr->scrollUp = scrollVdcUp;
	scr->scrollUpCol = scrollVdcUpCol;
	scr->fillMem = fillVdcMem;
	scr->copyScrToStr = copyVdcToStr;
}
