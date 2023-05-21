/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe character ROM demo. PETSCII is used instead of CP/M ASCII default.
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
	/* Use ram at end of bank 0 */
	initVicScr(scr, 0x3c00, 0x1800);
	initVicScrMode(scr, vicBlack, vicBlack, vicWhite);
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
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	uchar i;
	char str[40];
	(scr->print)(scr, 0, 0, "Simple character mode using ROM for the "
			"character set and one screen at the end "
			"of VIC bank 0. This leaves about 15K for"
			"your program. Once your program grows   "
			"beyond 0x3c00 you have to move to VIC   "
			"bank 1.");
	for (i = 0; i < 255; i++) {
		scr->scrMem[i + 280] = i;
	}
	sprintf(str, "mem: %04x", vicMem);
	(scr->printCol)(scr, 0, 15, vicLightBlue, str);
	sprintf(str, "chr: %04x", scr->chrMem);
	(scr->printCol)(scr, 0, 16, vicLightBlue, str);
	sprintf(str, "scr: %04x", scr->scrMem);
	(scr->printCol)(scr, 0, 17, vicLightBlue, str);
	waitKey(scr);
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
