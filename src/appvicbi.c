/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <screen.h>
#include <sys.h>
#include <vdc.h>
#include <vic.h>

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void initVicBmp(screen *scr, ushort bmpMem, ushort colMem, ushort chrMem, uchar bgCol, uchar fgCol, uchar pixCol) {
	uchar vicBank;
	initCia();
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
	/* Set border and background color */
	outp(vicBorderCol, vicLightBlue);
	outp(vicBgCol0, vicBlack);
	/* Clear bitmap */
	(scr->clearBmpCol)(scr, 0x00);
	/* Clear bitmap */
	(scr->clearBmp)(scr, 0);
	/* Set foreground and black background pixel colors */
	(scr->clearBmpCol)(scr, pixCol);
	/* Copy VDC alt char set to VIC mem */
	copyVdcChrMem(scr->bmpChrMem, 0x3000, 256);
	/* Set standard bitmap mode using MMU bank 1 */
	vicBank = (ushort) scr->bmpMem / 16384;
	setVicBmpMode(1, vicBank,
			((ushort) scr->bmpColMem - (vicBank * 16384)) / 1024,
			((ushort) scr->bmpMem - (vicBank * 16384)) / 8192);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}
