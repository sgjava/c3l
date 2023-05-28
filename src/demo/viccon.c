/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe character ROM demo. PETSCII is used instead of CP/M ASCII default.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

/*
 * Initialize key scan and screen.
 */
void init(console *con, screen *scr) {
	initCia();
	/* Use ram at end of bank 0 */
	initVicScr(scr, 0x3c00, 0x1800);
	initVicScrMode(scr, vicBlack, vicBlack, vicWhite);
	initCon(con, scr);
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
void run(console *con) {
	uchar i;
	for (i = 0; i < 20; i++) {
		printCon(con, "Where the sea meets the sky, dreams take flight on "
				"wings of hope, as whispers of adventure call to the "
				"intrepid souls seeking their destiny.");
	}
	waitKey(con->scr);
}

/*
 * Configure memory to protect VIC, save off screen and background colors and run demo.
 */
main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Create console struct */
	console *con = (console*) malloc(sizeof(console));
	/* Save screen/border color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(con, scr);
	run(con);
	done(border, background);
	/* Free memory */
	free(vicMem);
	free(scr);
	free(con);
}
