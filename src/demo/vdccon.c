/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC text demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <screen.h>
#include <stdlib.h>
#include <vdc.h>

/*
 * Initialize key scan, screen and console.
 */
void init(console *con, screen *scr) {
	initCia();
	initVdcScr(scr, vdcScrMem, vdcChrMem);
	initVdcScrMode(scr, vdcBlack, vdcWhite, vdcAltChrSet | vdcWhite);
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
 * Run demo.
 */
void run(console *con) {
	uchar i;
	for (i = 0; i < 40; i++) {
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
