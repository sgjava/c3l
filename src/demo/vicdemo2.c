/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe screen print demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

/*
 * Initialize key scan and screen.
 */
void init(screen *scr) {
	initCia();
	/* Use ram at end of bank 0 for screen and copy VDC character set just above that */
	initVicScr(scr, 0x3c00, 0x3000, vicBlack, vicBlack, vicWhite);
}

/*
 * Restore VIC back to CP/M defaults.
 */
void done(uchar bgCol, uchar fgCol) {
	doneVic(bgCol, fgCol);
	doneCia();
}

/*
 * Wait for Return key to be pressed.
 */
void waitKey(screen *scr) {
	(scr->printCol)(scr, 0, scr->scrHeight - 1, vicYellow, "Press Return");
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
	for (i = 0; i < 24; i++) {
		(scr->print)(scr, 0, i, "|Watch how fast you can fill the screen|");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth, scr->scrWidth,
			32);
	for (i = 0; i < 24; i++) {
		(scr->scrollUp)(scr, 1, 0, scr->scrWidth - 2, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Color text output.
 */
void fillScrCol(screen *scr) {
	register uchar i;
	(scr->clearScr)(scr, 32);
	for (i = 0; i < 24; i++) {
		(scr->printCol)(scr, 4, i, i / 2 + 1, "You can do color text as well");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth, scr->scrWidth,
			32);
	for (i = 0; i < 24; i++) {
		(scr->scrollUpCol)(scr, 4, 0, 32, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	char str[40];
	(scr->print)(scr, 0, 0, "Simple character mode using the VDC     "
			"character set, one screen and interrupts"
			"are disabled. Since no color is updated "
			"text output is blazing fast!");
	sprintf(str, "mem:    %04x", vicMem);
	(scr->print)(scr, 0, 6, str);
	sprintf(str, "chr:    %04x", scr->chrMem);
	(scr->print)(scr, 0, 7, str);
	sprintf(str, "scr:    %04x", scr->scrMem);
	(scr->print)(scr, 0, 8, str);
	waitKey(scr);
	fillScr(scr);
	fillScrCol(scr);
}

/*
 * Configure memory to protect VIC, save off screen and background colors and run demo.
 */
main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Save screen/border color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(scr);
	run(scr, vicMem);
	done(border, background);
	/* Free memory */
	free(vicMem);
	free(scr);
}
