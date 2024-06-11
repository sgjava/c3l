/*
 * C128 CP/M 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Copy fonts to memory, set screen struct for VDC and clear screen.
 */
void initVdcBmpMode(const bitmap *bmp, const unsigned char *chrMem, const unsigned char bgCol, const unsigned char fgCol) {
	saveVdc();
	/* Turn off cursor for bitmap mode */
	setVdcCursor(0, 0, vdcCurNone);
	/* Copy VDC char sets to mem bufer */
	copyVdcChrMem(chrMem, 0x2000, 512);
	/* Set bitmap mode */
	setVdcFgBg(bmp->color[fgCol], bmp->color[bgCol]);
	setVdcAttrsOff();
	setVdcBmpMode((unsigned int) bmp->bmpMem, (unsigned int) bmp->bmpColMem);
	(bmp->clearBmp)(bmp, 0);
}
