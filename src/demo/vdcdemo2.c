/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC text demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include <cia.h>
#include <vdc.h>
#include <screen.h>
#include <rtc.h>
#include "hitech.h"
#include "sys.h"

/*
 * Set screen color, screen memory and char set memory.
 * Clear screen and color memory then enable screen.
 */
void init() {
	/* Clear all CIA 1 IRQ enable bits */
	outp(cia1Icr, 0x7f);
	/* Clear CIA 1 ICR status */
	inp(cia1Icr);
	/* Clear all CIA 2 IRQ enable bits */
	outp(cia2Icr, 0x7f);
	/* Clear CIA 2 ICR status */
	inp(cia2Icr);
	/* Set CIA 1 DDRs for keyboard scan */
	outp(cia1DdrA, 0xff);
	outp(cia1DdrB, 0x00);
	/* Set default sizes and locations */
	scrWidth = 80;
	scrHeight = 25;
	scrSize = scrWidth * scrHeight;
	scrMem = (uchar*) vdcScrMem;
	scrColMem = (uchar*) vdcColMem;
	chrMem = (uchar*) vdcChrMem;
	/* Assign functions */
	clearScr = clearVdcScr;
	clearScrCol = clearVdcScrCol;
	print = printVdc;
	printCol = printVdcCol;
	saveVdc();
	setVdcCursor(0, 0, vdcCurNone);
	clearScr(32);
	setVdcFgBg(15, 0);
}

/*
 * Restore VDC and set screen for CP/M return.
 */
void done() {
	restoreVdc();
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, 0x82);
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
}

/*
 * Wait for Return.
 */
void waitKey() {
	printCol(0, 24, vdcAltChrSet | vdcLightYellow, " Press Return ");
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
void fillScr() {
	register uchar i;
	clearScr(32);
	clearScrCol(vdcAltChrSet | vdcLightGreen);
	for (i = 0; i < 24; i++) {
		print(0, i,
				"| Watch how fast you can fill the screen with text. CP/M will never be as fast |");
	}
	waitKey();
	/* Blank out bottom line */
	fillVdcMem((ushort) scrMem + scrSize - scrWidth, scrWidth, 32);
	for (i = 0; i < 24; i++) {
		scrollVdcUp(0, 0, scrWidth -1, scrHeight - 1);
	}
	waitKey();
}

/*
 * Color text output.
 */
void fillScrCol() {
	register uchar i;
	clearScr(32);
	clearScrCol(vdcAltChrSet | vdcBlack);
	for (i = 0; i < 24; i++) {
		printCol(i + 5, i, vdcAltChrSet | (i / 2 + 1),
				"You can do fast color text as well");
	}
	waitKey();
	/* Prime scroll */
	scrollVdcUpCol(0, 0, scrWidth -1, scrHeight - 1);
	/* Blank out bottom line */
	fillVdcMem((ushort) scrMem + scrSize - scrWidth, scrWidth, 32);
	fillVdcMem((ushort) scrColMem + scrSize - scrWidth, scrWidth, vdcBlack);
	for (i = 0; i < 24; i++) {
		scrollVdcUpCol(0, 0, scrWidth -1, scrHeight - 1);
	}
	waitKey();
}

/*
 * Run demo.
 */
void run() {
	char str[80];
	char *dateStr, *timeStr;
	setRtcMode(rtcDefaultMode);
	dateStr = getRtcDate();
	timeStr = getRtcTime();
	print(0, 0, "Simple character mode using the VDC "
			"character set, one screen and interrupts "
			"aredisabled. Since no color is updated "
			"text output is blazing fast!");
	sprintf(str, "Date:      %s", dateStr);
	print(0, 4, str);
	sprintf(str, "Time:      %s", timeStr);
	print(0, 5, str);
	sprintf(str, "scrMem:    %04x", scrMem);
	print(0, 6, str);
	sprintf(str, "scrColMem: %04x", scrColMem);
	print(0, 7, str);
	sprintf(str, "chrMem:    %04x", chrMem);
	print(0, 8, str);
	free(dateStr);
	free(timeStr);
	waitKey();
	fillScr();
	fillScrCol();
}

main() {
	init();
	run();
	done();
}
