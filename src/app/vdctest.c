/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <stdlib.h>
#include <vdc.h>

#include "demo.h"

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024

/*
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void init(const bitmap *bmp, const unsigned char *chr) {
	initCia();
	saveVdc();
	/* Turn off cursor for bitmap mode */
	setVdcCursor(0, 0, vdcCurNone);
	/* Copy VDC char sets to mem bufer */
	copyVdcChrMem(chr, 0x2000, 512);
	// Set 64K mode if not set
	if (!isVdc64k()) {
		setVdc64k();
	}
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
	setVdcFgBg(bmp->color[bmpBlack], bmp->color[bmpWhite]);
	setVdcAttrsOff();
	setVdcBmpMode(0x000, 0xc000);
	//(bmp->clearBmpCol)(bmp, (bmp->color[bmpWhite]));
	//(bmp->clearBmp)(bmp, 0);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done(const bitmap *bmp, const unsigned char *chr) {
	doneVdc();
	doneCia();
	/* Copy character set from memory to VDC */
	copyVdcMemChr(chr, 0x2000, 512);
}

/*
 * Run demo.
 */
void run() {
	int i;
	//runGraphDemo(bmp);
	//drawLine(bmp, 0, 0, bmp->bmpWidth - 1, 199, bmp->color[bmpWhite]);
	//(bmp->setPixel)(bmp, 0, 0, bmp->color[bmpWhite]);
	fillVdcMem(0x0000, 49152, 0);
	fillVdcMem(0x000 + 320, 1, 255);
	fillVdcMem(0x000 + 321, 1, 255);
	// Debounce
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	// Debounce
	while (getKey(0) == 0xfd)
		;
}

main() {
	/* Save both VDC char sets */
	unsigned char *chr = (unsigned char*) malloc(4096);
	init(chr);
	run();
	done(chr);
	/* Free memory */
	free(chr);
}
