/*
 * C128 CP/M C Library C3L
 *
 * C128 keyboard demo.
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
	(scr->printCol)(scr, 0, scr->scrHeight-1, vicYellow, "Press Return");
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
 * Simple screen line editor.
 */
void readLine(screen *scr) {
	char *str;
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Clear color to white */
	(scr->clearScrCol)(scr, vicWhite);
	(scr->printCol)(scr, 0, 0, 14, "Type in line and press return:");
	str = readVicLine(scr, 0, 2, scr->scrWidth);
	(scr->printCol)(scr, 0, 4, 14, "You entered:");
	(scr->printCol)(scr, 0, 6, 13, str);
	free(str);
	waitKey(scr);
}

/*
 * Display low level key scan and decoded key.
 */
void keyboard(screen *scr) {
	char str[40];
	uchar *ciaKeyScan, exitKey;
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Clear color to white */
	(scr->clearScrCol)(scr, vicWhite);
	(scr->print)(scr, 4, 0, "Standard and extended key scan");
	(scr->printCol)(scr, 0, 2, 14, " 0  1  2  3  4  5  6  7  8  9 10");
	(scr->printCol)(scr, 0, 6, 3, "Key pressed:");
	(scr->printCol)(scr, 0, 24, 1, "Press Return");
	do {
		ciaKeyScan = getKeys();
		exitKey = ciaKeyScan[0];
		sprintf(str, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
				ciaKeyScan[0], ciaKeyScan[1], ciaKeyScan[2], ciaKeyScan[3],
				ciaKeyScan[4], ciaKeyScan[5], ciaKeyScan[6], ciaKeyScan[7],
				ciaKeyScan[8], ciaKeyScan[9], ciaKeyScan[10]);
		(scr->print)(scr, 0, 4, str);
		free(ciaKeyScan);
		scr->scrMem[253] = decodeKey();
	} while (exitKey != 0xfd);
}

/*
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	char str[40];
	(scr->print)(scr, 0, 0, "Low level key scan of standard and      "
			"extended keyboard. You can also decode  "
			"unshifted and shifted characters. CIA 1 "
			"interrupts are disabled, so as not to   "
			"disrupt the key scan.");
	sprintf(str, "mem: %04x", vicMem);
	(scr->print)(scr, 0, 6, str);
	sprintf(str, "chr: %04x", scr->chrMem);
	(scr->print)(scr, 0, 7, str);
	sprintf(str, "scr: %04x", scr->scrMem);
	(scr->print)(scr, 0, 8, str);
	waitKey(scr);
	keyboard(scr);
	readLine(scr);
}

main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(scr);
	run(scr, vicMem);
	done(border, background);
	/* Free memory */
	free(vicMem);
	free(scr);
}
