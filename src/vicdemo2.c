/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe screen print demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include <sys.h>
#include <hitech.h>
#include <cia.h>
#include <vic.h>
#include <vdc.h>
#include <screen.h>
#include <rtc.h>

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and char set memory. Clear screen and color memory then enable screen.
 */
void init(uchar *chr) {
	uchar vicBank = (ushort) scrMem / 16384;
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
	/* Black screen and border */
	outp(vicBorderCol, 0);
	outp(vicBgCol0, 0);
	/* Clear color to white */
	clearScrCol(0);
	/* Clear screen */
	clearScr(32);
	/* Copy VDC alt char set to VIC mem */
	copyVdcChrMem(chr, 0x3000, 256);
	/* Set standard character mode using MMU bank 1 and set VIC based on scr location */
	setVicChrMode(1, vicBank, ((ushort) scrMem - (vicBank * 16384)) / 1024,
			((ushort) chr - (vicBank * 16384)) / 2048);
	/* Clear color to white */
	clearScrCol(1);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(uchar bgCol, uchar fgCol) {
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* Clear color to black */
	clearScrCol(0);
	/* CPM default */
	setVicChrMode(0, 0, 11, 3);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, 0x82);
}

/*
 * Wait for Return.
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
 * Text output without color.
 */
void fillScr() {
	register uchar i;
	for (i = 0; i < 24; i++) {
		print(0, i, "|Watch how fast you can fill the screen|");
	}
	waitKey();
	/* Blank out bottom line */
	fillVicMem((uchar*) scrMem + scrSize - scrWidth, scrWidth / 2, 0x2020);
	for (i = 0; i < 24; i++) {
		scrollVicUp(10, 0, scrWidth -1, scrHeight - 1);
	}
	waitKey();
}

/*
 * Color text output.
 */
void fillScrCol() {
	register uchar i;
	clearScr(32);
	for (i = 0; i < 24; i++) {
		printCol(4, i, i / 2 + 1, "You can do color text as well");
	}
	waitKey();
	/* Blank out bottom line */
	fillVicMem((uchar*) scrMem + scrSize - scrWidth, scrWidth / 2, 0x2020);
	for (i = 0; i < 24; i++) {
		scrollVicUpCol(10, 0, scrWidth -1, scrHeight - 1);
	}
	waitKey();
}

/*
 * Run demo.
 */
void run(uchar *scr, uchar *chr, uchar *vicMem) {
	char str[40];
	char *dateStr, *timeStr;
	setRtcMode(rtcDefaultMode);
	dateStr = getRtcDate();
	timeStr = getRtcTime();
	print(0, 0, "Simple character mode using the VDC     "
			"character set, one screen and interrupts"
			"are disabled. Since no color is updated "
			"text output is blazing fast!");
	sprintf(str, "Date:   %s", dateStr);
	print(0, 6, str);
	sprintf(str, "Time:   %s", timeStr);
	print(0, 7, str);
	sprintf(str, "vicMem: %04x", vicMem);
	print(0, 8, str);
	sprintf(str, "chrMem: %04x", chrMem);
	print(0, 9, str);
	sprintf(str, "scrMem: %04x", scrMem);
	print(0, 10, str);
	free(dateStr);
	free(timeStr);
	waitKey();
	fillScr();
	fillScrCol();
}

main() {
	/* Program is small enough to use left over bank 0 memory */
	uchar *vicMem = allocVicMem(0);
	/* Use space after ROM character set for RAM character set */
	uchar *chr = (uchar*) 0x3000;
	/* Use ram after character set for screen */
	uchar *scr = (uchar*) 0x3800;
	/* Save screen/border color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	scrWidth = 40;
	scrHeight = 25;
	scrSize = scrWidth * scrHeight;
	scrMem = scr;
	scrColMem = (uchar*) vicColMem;
	chrMem = chr;
	/* Set screen functions */
	clearScr = clearVicScr;
	clearScrCol = clearVicCol;
	/* Use VIC print functions */
	print = printVic;
	printCol = printVicCol;
	init(chr);
	run(scr, chr, vicMem);
	free(vicMem);
	done(border, background);
}
