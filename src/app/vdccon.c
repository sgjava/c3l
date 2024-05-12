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
#include <stdlib.h>
#include <vdc.h>

#include "demo.h"

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024

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
	runConDemo(con, 200);
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
