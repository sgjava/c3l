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
void initVicBmpMode(screen *scr, uchar bgCol, uchar fgCol, uchar pixCol) {
	uchar vicBank;
	/* Set border and background color */
	outp(vicBorderCol, fgCol);
	outp(vicBgCol0, bgCol);
	/* Clear bitmap */
	(scr->clearBmpCol)(scr, bgCol);
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
