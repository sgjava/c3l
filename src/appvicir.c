/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <screen.h>
#include <sys.h>
#include <vic.h>

/*
 * Initialize VIC using character ROM and ASCII to PETSCII conversion for print operations.
 */
void initVicScrRom(screen *scr, ushort scrMem, uchar bgCol, uchar fgCol, uchar chrCol) {
	uchar vicBank;
	initCia();
	/* VIC Screen configuration */
	scr->scrWidth = 40;
	scr->scrHeight = 25;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	/* Use ROM character set */
	scr->chrMem = (uchar*) 0x1800;
	/* This need to be bank 0 */
	scr->scrMem = (uchar*) scrMem;
	scr->scrColMem = (uchar*) vicColMem;
	scr->clearScr = clearVicScr;
	scr->clearScrCol = clearVicCol;
	scr->print = printVicPet;
	scr->printCol = printVicColPet;
	scr->scrollUp = scrollVicUp;
	scr->scrollUpCol = scrollVicUpCol;
	scr->fillMem = fillVicMem;
	/* Set screen and border color */
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* Clear char color to same as background color */
	(scr->clearScrCol)(scr, bgCol);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Set standard character mode using MMU bank 1 and set VIC based on scrMem location */
	vicBank = (ushort) scr->scrMem / 16384;
	setVicChrMode(1, vicBank, ((ushort) scr->scrMem - (vicBank * 16384)) / 1024,
			((ushort) scr->chrMem - (vicBank * 16384)) / 2048);
	/* Clear character color */
	(scr->clearScrCol)(scr, chrCol);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}
