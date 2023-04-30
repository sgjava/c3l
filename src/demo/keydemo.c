/*
 * C128 CP/M C Library C3L
 *
 * C128 keyboard demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <cia.h>
#include <vic.h>
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
 * Simple screen line editor.
 */
void readLine(screen *scr) {
	char *str;
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Clear color to white */
	(scr->clearScrCol)(scr, vicWhite);
	(scr->printCol)(scr, 0, 0, 14, "Type in line and press return:");
	str = readVicLine(scr, 0, 2, scr->scrWidth);
	(scr->printCol)(scr, 0, 4, 14, "You entered:");
	(scr->printCol)(scr, 0, 6, 13, str);
	free(str);
	waitKey(scr);
}

/*
 * Display low level key scan and decoded key.
 */
void keyboard(screen *scr) {
	char str[40];
	uchar *ciaKeyScan, exitKey;
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Clear color to white */
	(scr->clearScrCol)(scr, vicWhite);
	(scr->print)(scr, 4, 0, "Standard and extended key scan");
	(scr->printCol)(scr, 0, 2, 14, " 0  1  2  3  4  5  6  7  8  9 10");
	(scr->printCol)(scr, 0, 6, 3, "Key pressed:");
	(scr->printCol)(scr, 0, 24, 1, "Press Return");
	do {
		ciaKeyScan = getKeys();
		exitKey = ciaKeyScan[0];
		sprintf(str, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
				ciaKeyScan[0], ciaKeyScan[1], ciaKeyScan[2], ciaKeyScan[3],
				ciaKeyScan[4], ciaKeyScan[5], ciaKeyScan[6], ciaKeyScan[7],
				ciaKeyScan[8], ciaKeyScan[9], ciaKeyScan[10]);
		(scr->print)(scr, 0, 4, str);
		free(ciaKeyScan);
		scr->scrMem[253] = decodeKey();
	} while (exitKey != 0xfd);
}

/*
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	char str[40];
	(scr->print)(scr, 0, 0, "Low level key scan of standard and      "
			"extended keyboard. You can also decode  "
			"unshifted and shifted characters. CIA 1 "
			"interrupts are disabled, so as not to   "
			"disrupt the key scan.");
	sprintf(str, "mem: %04x", vicMem);
	(scr->print)(scr, 0, 6, str);
	sprintf(str, "chr: %04x", scr->chrMem);
	(scr->print)(scr, 0, 7, str);
	sprintf(str, "scr: %04x", scr->scrMem);
	(scr->print)(scr, 0, 8, str);
	waitKey(scr);
	keyboard(scr);
	readLine(scr);
}

main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(scr);
	run(scr, vicMem);
	done(scr, border, background);
	/* Free memory */
	free(vicMem);
	free(scr);
}
