/*
 * C128 CP/M C Library C3L
 *
 * C128 text performance comparison.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <hitech.h>
#include <screen.h>
#include <stdlib.h>
#include <vdc.h>
#include <vic.h>

#include "demo.h"

static ushort LINES = 23;

/*
 * Initialize key scan, VIC screen and console.
 */
void initVic(console *con, screen *scr) {
	/* Use ram at end of bank 1 for screen and copy VDC character set just above that */
	initVicScr(scr, 0x7c00, 0x7000);
	initVicScrMode(scr, scrBlack, scrBlack, scrWhite);
	initCon(con, scr);
}

/*
 * Initialize key scan, VDC screen and console.
 */
void initVdc(console *con, screen *scr) {
	initVdcScr(scr, vdcScrMem, vdcChrMem);
	initVdcScrMode(scr, scrBlack, scrBlack, scrWhite);
	initCon(con, scr);
}

/*
 * Restore VIC, VDC registers and CIA for CP/M return.
 */
void done() {
	doneVic();
	doneVdc();
	doneCia();
}

/*
 * Run demo.
 */
void run(console *vicCon, console *vdcCon, ushort cpmPrintMs, ushort cpmScrollMs, ushort lines) {
	runTextDemo(vicCon, vdcCon, cpmPrintMs, cpmScrollMs, lines);
	clearHomeCon(vdcCon);
	clearHomeCon(vicCon);
}

main() {
	ushort cpmMs = cpmPrint(LINES);
	ushort cpmScrollMs = cpmScroll(LINES);
	/* Program is small enough to use left over bank 1 memory */
	uchar *vicMem = allocVicMem(1);
	/* Create screen structs */
	screen *vicScr = (screen*) malloc(sizeof(screen));
	screen *vdcScr = (screen*) malloc(sizeof(screen));
	/* Create console structs */
	console *vicCon = (console*) malloc(sizeof(console));
	console *vdcCon = (console*) malloc(sizeof(console));
	initCia();
	initVic(vicCon, vicScr);
	initVdc(vdcCon, vdcScr);
	run(vicCon, vdcCon, cpmMs, cpmScrollMs, LINES);
	done();
	free(vicScr);
	free(vicCon);
	free(vicMem);
	free(vdcScr);
	free(vdcCon);
}
