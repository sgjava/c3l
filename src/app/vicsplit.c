/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe split screen bitmap/text  demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <console.h>
#include <demo.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vic.h>

extern void irq1(void);

/*
 * Initialize key scan, screen and bitmap.
 */
void init(const console *con, const screen *scr, const bitmap *bmp) {
	initCia();
	/* Use ram at end of bank 1 for text and bitmap */
	initVicScr(scr, 0x8800, 0x8000);
	initVicScrMode(scr, scrBlue, scrBlack, scrWhite);
	initCon(con, scr);
	initVicBmp(bmp, 0xa000, 0x8c00, 0x8000);
	/* Clear bitmap */
	(bmp->clearBmp)(bmp, 0);
	/* Set foreground and background pixel colors */
	(bmp->clearBmpCol)(bmp,
			(bmp->color[bmpWhite] << 4) | (bmp->color[bmpBlack] & 0x0f));
}

/*
 * Restore VIC back to CP/M defaults.
 */
void done() {
	doneVic();
	doneCia();
}

/*
 * Find IRQ code signature and run demo. If assembler code changes then signature must change as well.
 */
void run(const unsigned char *memEnd, const console *con, const bitmap *bmp) {
	unsigned int found;
	unsigned char *memStart = (unsigned char*) 0x0100;
	/* This is the z80 signature used to find the custom interrupt code inside vicSplitScr */
	static unsigned char target[] = { 0xf5, 0xc5, 0xe5, 0x01, 0x12, 0xd0 };
	// Run demo using extern irq1
	runGraphDemoI(con, bmp, irq1);
}

main() {
	/* Use ram in bank 2 */
	unsigned char *vicMem = allocVicMem(2);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Create console struct */
	console *con = (console*) malloc(sizeof(console));
	/* Create bitmap struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	init(con, scr, bmp);
	run(vicMem - 1, con, bmp);
	done();
	/* Free memory */
	free(vicMem);
}
