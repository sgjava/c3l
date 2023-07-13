/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <hitech.h>
#include <stdlib.h>
#include <vdc.h>

#include "demo.h"

/*
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void init(bitmap *bmp, uchar *chr) {
	initCia();
	initVdcBmp(bmp, vdcScrMem, vdcColMem, chr);
	initVdcBmpMode(bmp, chr, bmpBlack, bmpWhite);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done(bitmap *bmp, uchar *chr) {
	doneVdc();
	doneCia();
	/* Copy character set from memory to VDC */
	copyVdcMemChr(chr, 0x2000, 512);
}

/*
 * Run demo.
 */
void run(bitmap *bmp) {
	runGraphDemo(bmp);
}

main() {
	/* Save both VDC char sets */
	uchar *chr = (uchar*) malloc(4096);
	/* Create screen struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	init(bmp, chr);
	run(bmp);
	done(bmp, chr);
	/* Free memory */
	free(chr);
	free(bmp);
}
