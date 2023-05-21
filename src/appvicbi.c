/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vic.h>

/*
 * Initialize screen struct for VIC.
 */
void initVicBmp(screen *scr, ushort bmpMem, ushort colMem, ushort chrMem) {
	/* VIC bitmap configuration */
	scr->bmpChrMem = (uchar*) chrMem;
	scr->bmpColMem = (uchar*) colMem;
	scr->bmpMem = (uchar*) bmpMem;
	scr->bmpWidth = 320;
	scr->bmpHeight = 200;
	scr->bmpSize = ((ulong) scr->bmpWidth * scr->bmpHeight) / 8;
	scr->scrWidth = 40;
	scr->scrHeight = 25;
	scr->bmpColSize = scr->scrWidth * scr->scrHeight;
	scr->aspectRatio = 2;
	scr->clearBmp = clearVicBmp;
	scr->clearBmpCol = clearVicBmpCol;
	scr->setPixel = setVicPix;
	scr->drawLineH = drawVicLineH;
	scr->drawLineV = drawVicLineV;
	scr->printBmp = printVicBmp;
}
