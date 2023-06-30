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
void run(console *con) {
	runKeyDemo(con);
}

main() {
	/* Program is small enough to use left over bank 1 memory */
	uchar *vicMem = allocVicMem(1);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Create console struct */
	console *con = (console*) malloc(sizeof(console));
	init(con, scr);
	run(con);
	done();
	/* Free memory */
	free(vicMem);
	free(scr);
	free(con);
}
