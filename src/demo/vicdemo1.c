/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe character ROM demo. PETSCII is used instead of CP/M ASCII default.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include <cia.h>
#include <vic.h>
#include <screen.h>
#include "hitech.h"
#include "sys.h"

/*
 * Initialize screen and key scan.
 */
void init() {
	uchar vicBank = (ushort) scrMem / 16384;
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
	/* Black screen and border */
	outp(vicBorderCol, vicBlack);
	outp(vicBgCol0, vicBlack);
	/* Clear color to black */
	clearScrCol(vicBlack);
	/* Clear screen to spaces */
	clearScr(32);
	/* Set standard character mode using MMU bank 1 and set VIC based on scr location */
	setVicChrMode(1, vicBank, ((ushort) scrMem - (vicBank * 16384)) / 1024,
			((ushort) chrMem - (vicBank * 16384)) / 2048);
	/* Clear color to white */
	clearScrCol(vicWhite);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(uchar bgCol, uchar fgCol) {
	/* Restore screen/border colors */
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* Clear color to black */
	clearScrCol(vicBlack);
	/* CPM default */
	setVicChrMode(0, 0, 11, 3);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, 0x82);
}

/*
 * Wait for Return key to be pressed.
 */
void waitKey() {
	printCol(0, 24, 7, "Press Return");
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
void run(uchar *vicMem) {
	uchar i;
	char str[40];
	print(0, 0, "Simple character mode using ROM for the "
			"character set and one screen at the end "
			"of VIC bank 0. This leaves about 15K for"
			"your program. Once your program grows   "
			"beyond 0x3c00 you have to move to VIC   "
			"bank 1.");
	for (i = 0; i < 255; i++) {
		scrMem[i + 280] = i;
	}
	sprintf(str, "vicMem: %04x", vicMem);
	printCol(0, 15, vicLightBlue, str);
	sprintf(str, "chrMem: %04x", chrMem);
	printCol(0, 16, vicLightBlue, str);
	sprintf(str, "scrMem: %04x", scrMem);
	printCol(0, 17, vicLightBlue, str);
	waitKey();
}

/*
 * Configure memory to protect VIC, save off screen and background colors, set
 * character/screen/color memory locations, set print function pointers and run demo.
 */
main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Save screen/border color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	/* Use ROM character set */
	chrMem = (uchar*) 0x1800;
	/* Use ram at end of bank */
	scrMem = (uchar*) 0x3c00;
	/* Set default sizes and locations */
	scrWidth = 40;
	scrHeight = 25;
	scrSize = scrWidth * scrHeight;
	scrColMem = (uchar*) vicColMem;
	/* Set screen functions */
	clearScr = clearVicScr;
	clearScrCol = clearVicCol;
	/* Use VIC print functions (in this case PETSCII) */
	print = printVicPet;
	printCol = printVicColPet;
	init();
	run(vicMem);
	free(vicMem);
	done(border, background);
}
