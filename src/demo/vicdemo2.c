/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe screen print demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <cia.h>
#include <vic.h>
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
	uchar vicBank;
	initCia();
	/* VIC Screen configuration */
	scr->scrWidth = 40;
	scr->scrHeight = 25;
	scr->scrSize = scr->scrWidth * scr->scrHeight;
	/* Use space after ROM character set for RAM character set */
	scr->chrMem = (uchar*) 0x3000;
	/* Use ram after character set for screen */
	scr->scrMem = (uchar*) 0x3800;
	scr->scrColMem = (uchar*) vicColMem;
	scr->clearScr = clearVicScr;
	scr->clearScrCol = clearVicCol;
	scr->print = printVic;
	scr->printCol = printVicCol;
	scr->scrollUp = scrollVicUp;
	scr->scrollUpCol = scrollVicUpCol;
	scr->fillMem = fillVicMem;
	/* Black screen and border */
	outp(vicBorderCol, vicBlack);
	outp(vicBgCol0, vicBlack);
	/* Clear color to black */
	(scr->clearScrCol)(scr, vicBlack);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Copy VDC alt char set to VIC mem */
	copyVdcChrMem(scr->chrMem, 0x3000, 256);
	/* Set standard character mode using MMU bank 1 and set VIC based on scr location */
	vicBank = (ushort) scr->scrMem / 16384;
	setVicChrMode(1, vicBank, ((ushort) scr->scrMem - (vicBank * 16384)) / 1024,
			((ushort) scr->chrMem - (vicBank * 16384)) / 2048);
	/* Clear color to white */
	(scr->clearScrCol)(scr, vicWhite);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(screen *scr, uchar bgCol, uchar fgCol) {
	/* Restore screen/border colors */
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* Clear color to black */
	(scr->clearScrCol)(scr, vicBlack);
	/* CPM default */
	setVicChrMode(0, 0, 11, 3);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, 0x82);
}

/*
 * Wait for Return key to be pressed.
 */
void waitKey(screen *scr) {
	(scr->printCol)(scr, 0, 24, 7, "Press Return");
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
	for (i = 0; i < 24; i++) {
		(scr->print)(scr, 0, i, "|Watch how fast you can fill the screen|");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth,
			scr->scrWidth / 2, 0x2020);
	for (i = 0; i < 24; i++) {
		(scr->scrollUp)(scr, 1, 0, scr->scrWidth - 2, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Color text output.
 */
void fillScrCol(screen *scr) {
	register uchar i;
	(scr->clearScr)(scr, 32);
	for (i = 0; i < 24; i++) {
		(scr->printCol)(scr, 4, i, i / 2 + 1, "You can do color text as well");
	}
	waitKey(scr);
	/* Blank out bottom line */
	(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth,
			scr->scrWidth / 2, 0x2020);
	for (i = 0; i < 24; i++) {
		(scr->scrollUpCol)(scr, 4, 0, 32, scr->scrHeight - 1);
	}
	waitKey(scr);
}

/*
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	char str[40];
	char *dateStr, *timeStr;
	setRtcMode(rtcDefaultMode);
	dateStr = getRtcDate();
	timeStr = getRtcTime();
	(scr->print)(scr, 0, 0, "Simple character mode using the VDC     "
			"character set, one screen and interrupts"
			"are disabled. Since no color is updated "
			"text output is blazing fast!");
	sprintf(str, "Date:   %s", dateStr);
	(scr->print)(scr, 0, 6, str);
	sprintf(str, "Time:   %s", timeStr);
	(scr->print)(scr, 0, 7, str);
	sprintf(str, "mem:    %04x", vicMem);
	(scr->print)(scr, 0, 8, str);
	sprintf(str, "chr:    %04x", scr->chrMem);
	(scr->print)(scr, 0, 9, str);
	sprintf(str, "scr:    %04x", scr->scrMem);
	(scr->print)(scr, 0, 10, str);
	free(dateStr);
	free(timeStr);
	waitKey(scr);
	fillScr(scr);
	fillScrCol(scr);
}

/*
 * Configure memory to protect VIC, save off screen and background colors, set
 * character/screen/color memory locations, set print function pointers and run demo.
 */
main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Save screen/border color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(scr);
	run(scr, vicMem);
	done(scr, border, background);
	/* Free memory */
	free(vicMem);
	free(scr);
}
