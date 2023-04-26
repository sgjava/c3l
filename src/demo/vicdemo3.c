/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
 * Clear bitmap.
 */
void clearBitmap(screen *scr) {
	/* Set to black */
	(scr->clearBmpCol)(scr, 0x00);
	/* Clear bitmap */
	(scr->clearBmp)(scr, 0);
	/* White foreground and black background */
	(scr->clearBmpCol)(scr, 0x10);
}

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void init(screen *scr) {
	uchar vicBank;
	initCia();
	/* VIC Screen configuration */
	/* Use ram after character set for screen */
	scr->bmpChrMem = (uchar*) 0x8000;
	/* Use ram after character set for screen */
	scr->bmpColMem = (uchar*) 0x8800;
	/* Use bottom of bank 2 for bitmap */
	scr->bmpMem = (uchar*) 0xa000;
	scr->bmpWidth = 320;
	scr->bmpHeight = 200;
	scr->bmpSize = ((ulong) scr->bmpWidth * scr->bmpHeight) / 8;
	scr->scrWidth = 40;
	scr->scrHeight = 25;
	scr->bmpColSize = scr->scrWidth * scr->scrHeight;
	/* VIC aspect ratio */
	scr->aspectRatio = 2;
	/* Use VIC clear functions */
	scr->clearBmp = clearVicBmp;
	scr->clearBmpCol = clearVicBmpCol;
	/* Use VIC pixel functions */
	scr->setPixel = setVicPix;
	/* Use optimized horizontal and vertical lines on the VIC */
	scr->drawLineH = drawVicLineH;
	scr->drawLineV = drawVicLineV;
	/* Set screen and border color */
	outp(vicBorderCol, 14);
	outp(vicBgCol0, 0);
	/* Clear bitmap */
	clearBitmap(scr);
	/* Copy VDC alt char set to VIC mem */
	copyVdcChrMem(scr->bmpChrMem, 0x3000, 256);
	/* Set standard bitmap mode using MMU bank 1 */
	vicBank = (ushort) scr->bmpMem / 16384;
	setVicBmpMode(1, vicBank,
			((ushort) scr->bmpColMem - (vicBank * 16384)) / 1024,
			((ushort) scr->bmpMem - (vicBank * 16384)) / 8192);
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(screen *scr, uchar bgCol, uchar fgCol) {
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* Clear color to black */
	(scr->clearBmpCol)(scr, 0x10);
	/* CPM default */
	setVicChrMode(0, 0, 11, 3);
	free(scr);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, 0x82);
}

/*
 * Wait for Return.
 */
void waitKey(screen *scr) {
	printVicBmp(scr, 0, 24, 0x36, " Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	printVicBmp(scr, 0, 24, 0x36, " Erasing pixels ");
}

/*
 * Print centered text on top line in bitmap.
 */
void bannerBmp(screen *scr, char *str) {
	printVicBmp(scr, ((scr->scrWidth - strlen(str)) >> 1), 0, 0x36, str);
}

/*
 * Draw lines.
 */
void lines(screen *scr) {
	uchar i;
	bannerBmp(scr, " Bresenham lines ");
	for (i = 0; i < 16; i++) {
		drawLine(scr, 0, 0, i * 20, 199, 1);
		drawLine(scr, 319, 0, 319 - (i * 20), 199, 1);
	}
	waitKey(scr);
	for (i = 0; i < 16; i++) {
		drawLine(scr, 0, 0, i * 20, 199, 0);
		drawLine(scr, 319, 0, 319 - (i * 20), 199, 0);
	}
}

/*
 * Draw horizontal lines.
 */
void linesH(screen *scr) {
	uchar i;
	bannerBmp(scr, " Optimized horizontal lines ");
	for (i = 0; i < 159; i++) {
		drawLine(scr, i, i + 20, 319 - i, i + 20, 1);
	}
	waitKey(scr);
	for (i = 0; i < 159; i++) {
		drawLine(scr, i, i + 20, 319 - i, i + 20, 0);
	}
}

/*
 * Draw vertical lines.
 */
void linesV(screen *scr) {
	uchar i;
	bannerBmp(scr, " Optimized vertical lines ");
	for (i = 10; i < 199; i++) {
		drawLine(scr, i + 57, 10, i + 57, i + 1, 1);
	}
	waitKey(scr);
	for (i = 10; i < 199; i++) {
		drawLine(scr, i + 57, 10, i + 57, i + 1, 0);
	}
}

/*
 * Draw Bezier curves.
 */
void bezier(screen *scr) {
	uchar i;
	bannerBmp(scr, " Bezier curves ");
	for (i = 0; i < 35; i++) {
		drawBezier(scr, i * 5, 10, 319, 15 + i * 5, 319, 15 + i * 5, 1);
	}
	waitKey(scr);
	for (i = 0; i < 35; i++) {
		drawBezier(scr, i * 5, 10, 319, 15 + i * 5, 319, 15 + i * 5, 0);
	}
}

/*
 * Draw rectangles.
 */
void rectangles(screen *scr) {
	uchar i;
	bannerBmp(scr, " Rectangles ");
	for (i = 1; i < 30; i++) {
		drawRect(scr, i * 2, i * 2, (i * 10) + 20, (i * 5) + 20, 1);
	}
	waitKey(scr);
	for (i = 1; i < 30; i++) {
		drawRect(scr, i * 2, i * 2, (i * 10) + 20, (i * 5) + 20, 0);
	}
}

/*
 * Draw squares.
 */
void squares(screen *scr) {
	uchar i;
	bannerBmp(scr, " Squares ");
	for (i = 0; i < 10; i++) {
		drawSquare(scr, i * 8, i * 8, (i * 8) + 8, 1);
	}
	waitKey(scr);
	for (i = 0; i < 10; i++) {
		drawSquare(scr, i * 8, i * 8, (i * 8) + 8, 0);
	}
}

/*
 * Draw ellipses.
 */
void ellipses(screen *scr) {
	ushort i;
	bannerBmp(scr, " Ellipses ");
	for (i = 1; i < 9; i++) {
		drawEllipse(scr, 159, 99, i * 19, i * 10, 1);
	}
	waitKey(scr);
	for (i = 1; i < 9; i++) {
		drawEllipse(scr, 159, 99, i * 19, i * 10, 0);
	}
}

/*
 * Draw circles.
 */
void circles(screen *scr) {
	ushort i;
	bannerBmp(scr, " Circles ");
	for (i = 1; i < 12; i++) {
		drawCircle(scr, 159, 99, i * 10, 1);
	}
	waitKey(scr);
	for (i = 1; i < 12; i++) {
		drawCircle(scr, 159, 99, i * 10, 0);
	}
}

/*
 * Run demo.
 */
void run(screen *scr, uchar *vicMem) {
	char str[40];
	printVicBmp(scr, 0, 0, 0x16, "This demo will show off bitmap graphics."
			"Interrupts are disabled and getKey is   "
			"used to read keyboard.                  ");
	sprintf(str, "mem: %04x", vicMem);
	printVicBmp(scr, 0, 4, 0x12, str);
	sprintf(str, "chr: %04x", scr->bmpChrMem);
	printVicBmp(scr, 0, 6, 0x12, str);
	sprintf(str, "col: %04x", scr->bmpColMem);
	printVicBmp(scr, 0, 8, 0x12, str);
	sprintf(str, "bmp: %04x", scr->bmpMem);
	printVicBmp(scr, 0, 10, 0x12, str);
	waitKey(scr);
	clearBitmap(scr);
	lines(scr);
	clearBitmap(scr);
	linesH(scr);
	clearBitmap(scr);
	linesV(scr);
	clearBitmap(scr);
	bezier(scr);
	clearBitmap(scr);
	rectangles(scr);
	clearBitmap(scr);
	squares(scr);
	clearBitmap(scr);
	ellipses(scr);
	clearBitmap(scr);
	circles(scr);
}

main() {
	/* We need to use bank 2 since program is over 16K */
	uchar vicBank = 2;
	uchar *vicMem = allocVicMem(vicBank);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Save border/background color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(scr);
	run(scr, vicMem);
	done(scr, border, background);
	free(vicMem);
}
