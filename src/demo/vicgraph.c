/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <hitech.h>
#include <stdlib.h>
#include <vic.h>

#include "demo.h"

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void init(bitmap *bmp) {
	initCia();
	initVicBmp(bmp, 0x6000, 0x4800, 0x4000);
	initVicBmpMode(bmp, bmpBlack, bmpBlack, bmpWhite);
}

/*
 * Restore VIC back to CP/M defaults.
 */
void done() {
	doneVic();
	doneCia();
}


/*
 * Run demo.
 */
void run(bitmap *bmp) {
	runGraphDemo(bmp);
}

main() {
	/* We need to use bank 1 since program is close to 16K */
	uchar *vicMem = allocVicMem(1);
	/* Create bitmap struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	init(bmp);
	run(bmp);
	done();
	/* Free memory */
	free(vicMem);
	free(bmp);
}
