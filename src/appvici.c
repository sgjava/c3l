/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
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
 * Initialize VIC using  VDC alt character set in RAM.
 */
void initVicScr(screen *scr, ushort scrMem, ushort chrMem, uchar bgCol, uchar fgCol, uchar chrCol) {
	uchar vicBank;
	initCia();
	/* VIC Screen configuration */
	scr->scrWidth = 40;
	scr->scrHeight = 25;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	scr->chrMem = (uchar*) chrMem;
	scr->scrMem = (uchar*) scrMem;
	scr->scrColMem = (uchar*) vicColMem;
	scr->clearScr = clearVicScr;
	scr->clearScrCol = clearVicCol;
	scr->print = printVic;
	scr->printCol = printVicCol;
	scr->scrollUp = scrollVicUp;
	scr->scrollUpCol = scrollVicUpCol;
	scr->fillMem = fillVicMem;
	/* Black screen and border */
	outp(vicBorderCol, vicBlack);
	outp(vicBgCol0, vicBlack);
	/* Clear color to black */
	(scr->clearScrCol)(scr, vicBlack);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Copy VDC alt char set to VIC mem */
	copyVdcChrMem(scr->chrMem, 0x3000, 256);
	/* Set standard character mode using MMU bank 1 and set VIC based on scrMem location */
	vicBank = (ushort) scr->scrMem / 16384;
	setVicChrMode(1, vicBank, ((ushort) scr->scrMem - (vicBank * 16384)) / 1024,
			((ushort) scr->chrMem - (vicBank * 16384)) / 2048);
	/* Clear color to white */
	(scr->clearScrCol)(scr, chrCol);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}
