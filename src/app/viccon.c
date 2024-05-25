/*
 * C128 CP/M C Library C3L
 *
 * C128 console demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <screen.h>
#include <stdlib.h>
#include <vic.h>

#include "demo.h"

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024
// Protect VIC memory < 0x8000
#pragma output CRT_HEAP_ADDRESS = 0x8000

/*
 * Initialize key scan, screen and console.
 */
void init(const console *con, const screen *scr) {
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
void run(const console *con) {
	runConDemo(con, 100);
}

/*
 * Configure memory to protect VIC and run demo.
 */
main() {
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Create console struct */
	console *con = (console*) malloc(sizeof(console));
	init(con, scr);
	run(con);
	done();
	/* Free memory */
	free(scr);
	free(con);
}
