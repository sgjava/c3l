/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <sys.h>
#include <vic.h>

/*
 * Initialize VIC using VDC alt character set in RAM.
 */
void initVicScrMode(screen *scr, uchar bgCol, uchar fgCol, uchar chrCol) {
	uchar vicBank;
	/* Black screen and border */
	outp(vicBorderCol, fgCol);
	outp(vicBgCol0, bgCol);
	/* Clear color to fgCol */
	(scr->clearScrCol)(scr, fgCol);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Only copy VDC character set if RAM used */
	if ((ushort) scr->chrMem != 0x1000 && (ushort) scr->chrMem != 0x1800) {
		/* Copy VDC alt char set to VIC mem */
		copyVdcChrMem(scr->chrMem, 0x3000, 256);
	}
	/* Set standard character mode using MMU bank 1 and set VIC based on scrMem location */
	vicBank = (ushort) scr->scrMem / 16384;
	setVicChrMode(1, vicBank, ((ushort) scr->scrMem - (vicBank * 16384)) / 1024,
			((ushort) scr->chrMem - (vicBank * 16384)) / 2048);
	/* Clear color */
	(scr->clearScrCol)(scr, chrCol);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}
