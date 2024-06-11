/*
 * C128 CP/M 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Copy fonts to memory for VDC interlace mode and clear screen.
 */
void initVdcIntBmpMode(const bitmap *bmp, const unsigned char *chrMem, const unsigned char bgCol, const unsigned char fgCol) {
	saveVdc();
	/* Turn off cursor for bitmap mode */
	setVdcCursor(0, 0, vdcCurNone);
	/* Copy VDC char sets to mem bufer */
	copyVdcChrMem(chrMem, 0x2000, 512);
	setVdcAttrsOff();
	setVdcBmpMode((unsigned int) bmp->bmpMem, (unsigned int) bmp->bmpColMem);
	outVdc(vdcHzTotal, 126);
	outVdc(vdcHzDisp, 80);
	outVdc(vdcHzSyncPos, 102);
	outVdc(vdcVtTotal, 76);
	outVdc(vdcVtTotalAdj, 6);
	outVdc(vdcVtDisp, 76);
	outVdc(vdcVtSyncPos, 71);
	outVdc(vdcIlaceMode, 3);
	outVdc(vdcChTotalVt, 6);
	outVdc(vdcVtSmScroll, 0);
	outVdc(vdcHzSmScroll, 135);
	outVdc(vdcAddrIncPerRow, 0);
	/* Set bitmap mode */
	setVdcFgBg(bmp->color[fgCol], bmp->color[bgCol]);
	setVdcAttrsOn();
	setVdcBmpMode((unsigned int) bmp->bmpMem, (unsigned int) bmp->bmpColMem);
	(bmp->clearBmp)(bmp, 0);
}
