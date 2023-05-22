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
void initVdcBmpMode(screen *scr, uchar *chrMem, uchar bgCol, uchar fgCol, uchar pixCol) {
	initCia();
	saveVdc();
	/* Turn off cursor for bitmap mode */
	setVdcCursor(0, 0, vdcCurNone);
	/* Copy VDC char sets to mem bufer */
	copyVdcChrMem(chrMem, 0x2000, 512);
	/* Set bitmap mode */
	setVdcFgBg(fgCol, bgCol);
	setVdcAttrsOff();
	setVdcBmpMode((ushort) scr->bmpMem, (ushort) scr->bmpColMem);
	(scr->clearBmp)(scr, pixCol);
}
