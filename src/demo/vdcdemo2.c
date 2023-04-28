/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC text demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cia.h>
#include <vdc.h>
#include <rtc.h>
#include "hitech.h"
#include "sys.h"

/*
 * Configure CIA to kill interrupts and enable keyboard scan.
 */
void initCia() {
	/* Clear all CIA 1 IRQ enable bits */
	outp(cia1Icr, ciaClearIcr);
	/* Clear CIA 1 ICR status */
	inp(cia1Icr);
	/* Clear all CIA 2 IRQ enable bits */
	outp(cia2Icr, ciaClearIcr);
	/* Clear CIA 2 ICR status */
	inp(cia2Icr);
	/* Set CIA 1 DDRs for keyboard scan */
	outp(cia1DdrA, 0xff);
	outp(cia1DdrB, 0x00);
}

/*
 * Initialize key scan and screen.
 */
void init(screen *scr) {
	initCia();
	/* VIC Screen configuration */
	scr->scrWidth = 80;
	scr->scrHeight = 25;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	scr->chrMem = (uchar*) vdcChrMem;
	scr->scrMem = (uchar*) vdcScrMem;
	scr->scrColMem = (uchar*) vdcColMem;
	scr->clearScr = clearVdcScr;
	scr->clearScrCol = clearVdcScrCol;
	scr->print = printVdc;
	scr->printCol = printVdcCol;
	scr->scrollUp = scrollVdcUp;
	scr->scrollUpCol = scrollVdcUpCol;
	scr->fillMem = fillVdcMem;
	saveVdc();
	setVdcCursor(0, 0, vdcCurNone);
	(scr->clearScr)(scr, 32);
	setVdcFgBg(vdcWhite, vdcBlack);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done() {
	restoreVdc();
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, ciaEnableIrq);
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
}

/*
 * Wait for Return.
 */
void waitKey(screen *scr) {
	(scr->printCol)(scr, 0, 24, vdcAltChrSet | vdcLightYellow,
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
 * Text output without color.
 */
void fillScr(screen *scr) {
	register uchar i;
	(scr->clearScr)(scr, 32);
	(scr->clearScrCol)(scr, vdcAltChrSet | vdcLightGreen);
	for (i = 0; i < 24; i++) {
		(scr->print)(scr, 0, i,
				"| Watch how fast you can fill the screen with text. CP/M will never be as fast |");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth,
			scr->scrWidth, 32);
	for (i = 0; i < 24; i++) {
		(scr->scrollUp)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Color text output.
 */
void fillScrCol(screen *scr) {
	register uchar i;
	(scr->clearScr)(scr, 32);
	(scr->clearScrCol)(scr, vdcAltChrSet | vdcBlack);
	for (i = 0; i < 24; i++) {
		(scr->printCol)(scr, i + 5, i, vdcAltChrSet | (i / 2 + 1),
				"You can do fast color text as well");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth,
			scr->scrWidth, 32);
	(scr->fillMem)(scr->scrColMem + scr->scrSize - scr->scrWidth,
			scr->scrWidth, vdcBlack);
	for (i = 0; i < 24; i++) {
		(scr->scrollUpCol)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Run demo.
 */
void run(screen *scr) {
	char str[80];
	char *dateStr, *timeStr;
	setRtcMode(rtcDefaultMode);
	dateStr = getRtcDate();
	timeStr = getRtcTime();
	(scr->print)(scr, 0, 0, "Simple character mode using the VDC "
			"character set, one screen and interrupts "
			"aredisabled. Since no color is updated "
			"text output is blazing fast!");
	sprintf(str, "Date:      %s", dateStr);
	(scr->print)(scr, 0, 4, str);
	sprintf(str, "Time:      %s", timeStr);
	(scr->print)(scr, 0, 5, str);
	sprintf(str, "scr:       %04x", scr->scrMem);
	(scr->print)(scr, 0, 6, str);
	sprintf(str, "col:       %04x", scr->scrColMem);
	(scr->print)(scr, 0, 7, str);
	sprintf(str, "chr:       %04x", scr->chrMem);
	(scr->print)(scr, 0, 8, str);
	free(dateStr);
	free(timeStr);
	waitKey(scr);
	fillScr(scr);
	fillScrCol(scr);
}

main() {
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	init(scr);
	run(scr);
	done();
	free(scr);
}
