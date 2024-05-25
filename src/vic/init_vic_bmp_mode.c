/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <bitmap.h>
#include <vdc.h>
#include <vic.h>

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void initVicBmpMode(const bitmap *bmp, const unsigned char bgCol, const unsigned char fgCol, const unsigned char pixCol) {
	unsigned char vicBank;
	saveVic();
	/* Set border and background color */
	outp(vicBorderCol, bmp->color[fgCol]);
	outp(vicBgCol0, bmp->color[bgCol]);
	/* Clear bitmap */
	(bmp->clearBmp)(bmp, 0);
	/* Set foreground and background pixel colors */
	(bmp->clearBmpCol)(bmp, (bmp->color[pixCol] << 4) | (bmp->color[bgCol] & 0x0f));
	/* Copy VDC alt char set to VIC mem */
	copyVdcChrMem(bmp->bmpChrMem, 0x3000, 256);
	/* Set standard bitmap mode using MMU bank 1 */
	vicBank = (unsigned int) bmp->bmpMem / 16384;
	setVicBmpMode(1, vicBank,
			((unsigned int) bmp->bmpColMem - (vicBank * 16384)) / 1024,
			((unsigned int) bmp->bmpMem - (vicBank * 16384)) / 8192);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}
