/*
 * C128 CP/M C Library C3L
 *
 * C128 keyboard demo.
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
#include "demo.h"

/*
 * Initialize key scan, screen and console.
 */
void init(console *con, screen *scr) {
	initCia();
	/* Use ram at end of bank 1 for screen and copy VDC character set just above that */
	initVicScr(scr, 0x7c00, 0x7000);
	initVicScrMode(scr, scrBlack, scrBlack, scrWhite);
	initCon(con, scr);
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
void run(console *con, uchar *vicMem) {
	screen *scr = con->scr;
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
	readLine(con);
}

main() {
	/* Program is small enough to use left over bank 1 memory */
	uchar *vicMem = allocVicMem(1);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Create console struct */
	console *con = (console*) malloc(sizeof(console));
	init(con, scr);
	run(con, vicMem);
	done();
	/* Free memory */
	free(vicMem);
	free(scr);
	free(con);
}
