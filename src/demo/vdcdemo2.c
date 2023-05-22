/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC text demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <vdc.h>

/*
 * Initialize key scan and screen.
 */
void init(screen *scr) {
	initCia();
	initVdcScr(scr, vdcScrMem, vdcChrMem);
	initVdcScrMode(scr, vdcBlack, vdcWhite, vdcAltChrSet | vdcWhite);
}

/*
 * Restore VDC registers and CIA for CP/M return.
 */
void done() {
	doneVdc();
	doneCia();
}

/*
 * Wait for Return.
 */
void waitKey(screen *scr) {
	(scr->printCol)(scr, 0, scr->scrHeight - 1, vdcAltChrSet | vdcLightYellow,
			" Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
}

/*
 * Text output without color.
 */
void fillScr(screen *scr) {
	register uchar i;
	(scr->clearScr)(scr, 32);
	(scr->clearScrCol)(scr, vdcAltChrSet | vdcLightGreen);
	for (i = 0; i < 24; i++) {
		(scr->print)(scr, 0, i,
				"| Watch how fast you can fill the screen with text. CP/M will never be as fast |");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth, scr->scrWidth,
			32);
	for (i = 0; i < 24; i++) {
		(scr->scrollUp)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Color text output.
 */
void fillScrCol(screen *scr) {
	register uchar i;
	(scr->clearScr)(scr, 32);
	(scr->clearScrCol)(scr, vdcAltChrSet | vdcBlack);
	for (i = 0; i < 24; i++) {
		(scr->printCol)(scr, i + 5, i, vdcAltChrSet | (i / 2 + 1),
				"You can do fast color text as well");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth, scr->scrWidth,
			32);
	(scr->fillMem)(scr->scrColMem + scr->scrSize - scr->scrWidth, scr->scrWidth,
			vdcBlack);
	for (i = 0; i < 24; i++) {
		(scr->scrollUpCol)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Run demo.
 */
void run(screen *scr) {
	char str[80];
	(scr->print)(scr, 0, 0, "Simple character mode using the VDC "
			"character set, one screen and interrupts "
			"aredisabled. Since no color is updated "
			"text output is blazing fast!");
	sprintf(str, "scr:       %04x", scr->scrMem);
	(scr->print)(scr, 0, 4, str);
	sprintf(str, "col:       %04x", scr->scrColMem);
	(scr->print)(scr, 0, 5, str);
	sprintf(str, "chr:       %04x", scr->chrMem);
	(scr->print)(scr, 0, 6, str);
	waitKey(scr);
	fillScr(scr);
	fillScrCol(scr);
}

main() {
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	init(scr);
	run(scr);
	done();
	free(scr);
}
