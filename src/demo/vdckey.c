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
#include <vdc.h>
#include "demo.h"

/*
 * Initialize key scan, screen and console.
 */
void init(console *con, screen *scr) {
	initCia();
	initVdcScr(scr, vdcScrMem, vdcChrMem);
	initVdcScrMode(scr, scrBlack, scrBlack, scrWhite);
	initCon(con, scr);
}

/*
 * Restore VDC registers and CIA for CP/M return.
 */
void done() {
	doneVdc();
	doneCia();
}

/*
 * Run demo.
 */
void run(console *con) {
	screen *scr = con->scr;
	char str[40];
	(scr->print)(scr, 0, 0, "Low level key scan of standard and extended keyboard. You can also decode unshifted and shifted characters. CIA 1 interrupts are disabled, so as not to disrupt the key scan.");
	sprintf(str, "chr: %04x", scr->chrMem);
	(scr->print)(scr, 0, 6, str);
	sprintf(str, "scr: %04x", scr->scrMem);
	(scr->print)(scr, 0, 7, str);
	waitKey(scr);
	keyboard(scr);
	readLine(con);
}

main() {
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Create console struct */
	console *con = (console*) malloc(sizeof(console));
	init(con, scr);
	run(con);
	done();
	free(scr);
	free(con);
}
