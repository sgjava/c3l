/*
 * C128 CP/M 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void initVdcBmp(screen *scr, ushort bmpMem, ushort colMem, uchar *chrMem,
		uchar bgCol, uchar fgCol, uchar pixCol) {
	initCia();
	saveVdc();
	/* Turn off cursor for bitmap mode */
	setVdcCursor(0, 0, vdcCurNone);
	/* Copy VDC char sets to VIC mem */
	copyVdcChrMem(chrMem, 0x2000, 512);
	/* VDC Screen configuration */
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
	/* Set bitmap mode */
	setVdcFgBg(fgCol, bgCol);
	setVdcAttrsOff();
	setVdcBmpMode((ushort) scr->bmpMem, (ushort) scr->bmpColMem);
	(scr->clearBmp)(scr, pixCol);
}
