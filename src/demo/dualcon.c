/*
 * C128 CP/M C Library C3L
 *
 * C128 dual display console demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <vdc.h>
#include <vic.h>

#include "demo.h"

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
 * Generate random sentences on both VIC and VDC,
 */
void randSentence(console *vicCon, console *vdcCon, uchar sentences, uchar color) {
	static uchar colors[] = { scrGreen, scrLightGreen, scrBlue, scrLightBlue,
	scrRed, scrLightRed};
	uchar i;
	char *str;
	if (color) {
		vicCon->colorOn = 1;
		vdcCon->colorOn = 1;
	} else {
		vicCon->colorOn = 0;
		vdcCon->colorOn = 0;
	}
	srand(inp(vicRaster));
	for (i = 0; i < sentences; i++) {
		if (color) {
			vicCon->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
			vdcCon->color = colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
		}
		str = generateSentence();
		printWrapCon(vicCon, str);
		free(str);
		if (vicCon->curX != 0) {
			printCon(vicCon, " ");
		}
		str = generateSentence();
		printWrapCon(vdcCon, str);
		free(str);
		if (vdcCon->curX != 0) {
			printCon(vdcCon, " ");
		}
	}
	printLineCon(vicCon, "");
	printLineCon(vdcCon, "");
}

/*
 * Run demo.
 */
void run(console *vicCon, console *vdcCon) {
    randSentence(vicCon, vdcCon, 100, 0);
    randSentence(vicCon, vdcCon, 100, 1);
	waitKey(vicCon->scr);
}

main() {
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
	run(vicCon, vdcCon);
	done();
	free(vicScr);
	free(vicCon);
	free(vicMem);
	free(vdcScr);
	free(vdcCon);
}
