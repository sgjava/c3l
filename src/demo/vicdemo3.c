/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <screen.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>
#include <vic.h>

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void init(screen *scr) {
	initCia();
	initVicBmp(scr, 0x6000, 0x4800, 0x4000);
	initVicBmpMode(scr, vicBlack, vicLightBlue, 0x10);
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(uchar bgCol, uchar fgCol) {
	doneVic(bgCol, fgCol);
	doneCia();
}

/*
 * Clear bitmap.
 */
void clearBitmap(screen *scr) {
	/* Set color to black */
	(scr->clearBmpCol)(scr, 0x00);
	/* Clear bitmap */
	(scr->clearBmp)(scr, 0);
	/* White foreground and black background */
	(scr->clearBmpCol)(scr, 0x10);
}

/*
 * Wait for Return.
 */
void waitKey(screen *scr) {
	printVicBmp(scr, 0, 24, " Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	(scr->printBmp)(scr, 0, 24, " Erasing pixels ");
}

/*
 * Print centered text on top line in bitmap.
 */
void bannerBmp(screen *scr, char *str) {
	(scr->printBmp)(scr, ((scr->scrWidth - strlen(str)) >> 1), 0, str);
}

/*
 * Draw lines.
 */
void lines(screen *scr) {
	uchar i;
	bannerBmp(scr, " Bresenham lines ");
	for (i = 0; i < 16; i++) {
		drawLine(scr, 0, 0, i * 20, scr->bmpHeight - 1, 1);
		drawLine(scr, scr->bmpWidth - 1, 0, scr->bmpWidth - 1 - (i * 20),
				scr->bmpHeight - 1, 1);
	}
	waitKey(scr);
	for (i = 0; i < 16; i++) {
		drawLine(scr, 0, 0, i * 20, scr->bmpHeight - 1, 0);
		drawLine(scr, scr->bmpWidth - 1, 0, scr->bmpWidth - 1 - (i * 20),
				scr->bmpHeight - 1, 0);
	}
}

/*
 * Draw horizontal lines.
 */
void linesH(screen *scr) {
	uchar i;
	bannerBmp(scr, " Optimized horizontal lines ");
	for (i = 0; i < 159; i++) {
		drawLine(scr, i, i + 20, scr->bmpWidth - 1 - i, i + 20, 1);
	}
	waitKey(scr);
	for (i = 0; i < 159; i++) {
		drawLine(scr, i, i + 20, scr->bmpWidth - 1 - i, i + 20, 0);
	}
}

/*
 * Draw vertical lines.
 */
void linesV(screen *scr) {
	uchar i;
	bannerBmp(scr, " Optimized vertical lines ");
	for (i = 10; i < scr->bmpHeight - 1; i++) {
		drawLine(scr, i + 57, 10, i + 57, i + 1, 1);
	}
	waitKey(scr);
	for (i = 10; i < scr->bmpHeight - 1; i++) {
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
		drawBezier(scr, i * 5, 10, scr->bmpWidth - 1, 15 + i * 5,
				scr->bmpWidth - 1, 15 + i * 5, 1);
	}
	waitKey(scr);
	for (i = 0; i < 35; i++) {
		drawBezier(scr, i * 5, 10, scr->bmpWidth - 1, 15 + i * 5,
				scr->bmpWidth - 1, 15 + i * 5, 0);
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
	(scr->printBmp)(scr, 0, 0, "This demo will show off bitmap graphics."
			"Interrupts are disabled and getKey is   "
			"used to read keyboard.                  ");
	sprintf(str, "mem: %04x", vicMem);
	(scr->printBmp)(scr, 0, 4, str);
	sprintf(str, "chr: %04x", scr->bmpChrMem);
	(scr->printBmp)(scr, 0, 6, str);
	sprintf(str, "col: %04x", scr->bmpColMem);
	(scr->printBmp)(scr, 0, 8, str);
	sprintf(str, "bmp: %04x", scr->bmpMem);
	(scr->printBmp)(scr, 0, 10, str);
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
	/* We need to use bank 1 since program is close to 16K */
	uchar *vicMem = allocVicMem(1);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Save border/background color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(scr);
	run(scr, vicMem);
	done(border, background);
	/* Free memory */
	free(vicMem);
	free(scr);
}
