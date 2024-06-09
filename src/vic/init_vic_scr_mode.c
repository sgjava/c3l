/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <screen.h>
#include <vdc.h>
#include <vic.h>

/*
 * Initialize VIC using VDC alt character set in RAM.
 */
void initVicScrMode(const screen *scr, const unsigned char bgCol, const unsigned char fgCol, const unsigned char chrCol) {
	unsigned char vicBank;
	saveVic();
	/* Black screen and border */
	outp(vicBorderCol, scr->color[fgCol]);
	outp(vicBgCol0, scr->color[bgCol]);
	/* Clear color to chrCol */
	(scr->clearScrCol)(scr, chrCol);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Only copy VDC character set if RAM used */
	if ((unsigned int) scr->chrMem != 0x1000 && (unsigned int) scr->chrMem != 0x1800 && (unsigned int) scr->chrMem != 0x9000
			&& (unsigned int) scr->chrMem != 0x9800) {
		/* Copy VDC alt char set to VIC mem */
		copyVdcChrMem(scr->chrMem, 0x3000, 256);
	}
	/* Set standard character mode using MMU bank 1 and set VIC based on scrMem location */
	vicBank = (unsigned int) scr->scrMem / 16384;
	setVicChrMode(1, vicBank, ((unsigned int) scr->scrMem - (vicBank * 16384)) / 1024,
			((unsigned int) scr->chrMem - (vicBank * 16384)) / 2048);
	/* Enable screen */
	outp(vicCtrlReg1, ((inp(vicCtrlReg1) | 0x10) & 0x7f));
}
