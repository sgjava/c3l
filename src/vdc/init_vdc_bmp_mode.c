/*
 * C128 CP/M 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <bitmap.h>
#include <vdc.h>

/*
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void initVdcBmpMode(bitmap *bmp, unsigned char *chrMem, unsigned char bgCol, unsigned char fgCol) {
	initCia();
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
