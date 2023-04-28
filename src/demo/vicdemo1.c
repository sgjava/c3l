/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe character ROM demo. PETSCII is used instead of CP/M ASCII default.
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
	/* Use ROM character set */
	scr->chrMem = (uchar*) 0x1800;
	/* Use ram at end of bank 0 */
	scr->scrMem = (uchar*) 0x3c00;
	scr->scrColMem = (uchar*) vicColMem;
	scr->clearScr = clearVicScr;
	scr->clearScrCol = clearVicCol;
	scr->print = printVicPet;
	scr->printCol = printVicColPet;
	/* Black screen and border */
	outp(vicBorderCol, vicBlack);
	outp(vicBgCol0, vicBlack);
	/* Clear color to black */
	(scr->clearScrCol)(scr, vicBlack);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
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
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	uchar i;
	char str[40];
	(scr->print)(scr, 0, 0, "Simple character mode using ROM for the "
			"character set and one screen at the end "
			"of VIC bank 0. This leaves about 15K for"
			"your program. Once your program grows   "
			"beyond 0x3c00 you have to move to VIC   "
			"bank 1.");
	for (i = 0; i < 255; i++) {
		scr->scrMem[i + 280] = i;
	}
	sprintf(str, "mem: %04x", vicMem);
	(scr->printCol)(scr, 0, 15, vicLightBlue, str);
	sprintf(str, "chr: %04x", scr->chrMem);
	(scr->printCol)(scr, 0, 16, vicLightBlue, str);
	sprintf(str, "scr: %04x", scr->scrMem);
	(scr->printCol)(scr, 0, 17, vicLightBlue, str);
	waitKey(scr);
}

/*
 * Configure memory to protect VIC, save off screen and background colors, set
 * character/screen/color memory locations, set print function pointers and run demo.
 */
main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(1);
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
