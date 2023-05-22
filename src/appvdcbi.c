/*
 * C128 CP/M 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Initialize screen struct for VIC.
 */
void initVdcBmp(screen *scr, ushort bmpMem, ushort colMem, uchar *chrMem) {
	/* VDC Screen configuration */
	/* Use the alternate character set 0x0800 offset */
	scr->bmpChrMem = (uchar*) ((ushort) chrMem) + 0x0800;
	scr->bmpColMem = (uchar*) colMem;
	scr->bmpMem = (uchar*) bmpMem;
	scr->bmpWidth = 640;
	scr->bmpHeight = 200;
	scr->bmpSize = ((ulong) scr->bmpWidth * scr->bmpHeight) / 8;
	scr->scrWidth = 80;
	scr->scrHeight = 25;
	scr->bmpColSize = scr->scrWidth * scr->scrHeight;
	scr->aspectRatio = 3;
	scr->clearBmp = clearVdcBmp;
	scr->clearBmpCol = clearVdcBmpCol;
	scr->setPixel = setVdcPix;
	scr->drawLineH = drawVdcLineH;
	scr->drawLineV = drawVdcLineV;
	scr->printBmp = printVdcBmp;
}
