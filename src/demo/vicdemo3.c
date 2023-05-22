/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <bitmap.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>
#include <vic.h>

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void init(bitmap *bmp) {
	initCia();
	initVicBmp(bmp, 0x6000, 0x4800, 0x4000);
	initVicBmpMode(bmp, vicBlack, vicLightBlue, 0x10);
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
void clearBitmap(bitmap *bmp) {
	/* Set color to black */
	(bmp->clearBmpCol)(bmp, 0x00);
	/* Clear bitmap */
	(bmp->clearBmp)(bmp, 0);
	/* White foreground and black background */
	(bmp->clearBmpCol)(bmp, 0x10);
}

/*
 * Wait for Return.
 */
void waitKey(bitmap *bmp) {
	printVicBmp(bmp, 0, 24, " Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	(bmp->printBmp)(bmp, 0, 24, " Erasing pixels ");
}

/*
 * Print centered text on top line in bitmap.
 */
void bannerBmp(bitmap *bmp, char *str) {
	(bmp->printBmp)(bmp, ((bmp->scrWidth - strlen(str)) >> 1), 0, str);
}

/*
 * Draw lines.
 */
void lines(bitmap *bmp) {
	uchar i;
	bannerBmp(bmp, " Bresenham lines ");
	for (i = 0; i < 16; i++) {
		drawLine(bmp, 0, 0, i * 20, bmp->bmpHeight - 1, 1);
		drawLine(bmp, bmp->bmpWidth - 1, 0, bmp->bmpWidth - 1 - (i * 20),
				bmp->bmpHeight - 1, 1);
	}
	waitKey(bmp);
	for (i = 0; i < 16; i++) {
		drawLine(bmp, 0, 0, i * 20, bmp->bmpHeight - 1, 0);
		drawLine(bmp, bmp->bmpWidth - 1, 0, bmp->bmpWidth - 1 - (i * 20),
				bmp->bmpHeight - 1, 0);
	}
}

/*
 * Draw horizontal lines.
 */
void linesH(bitmap *bmp) {
	uchar i;
	bannerBmp(bmp, " Optimized horizontal lines ");
	for (i = 0; i < 159; i++) {
		drawLine(bmp, i, i + 20, bmp->bmpWidth - 1 - i, i + 20, 1);
	}
	waitKey(bmp);
	for (i = 0; i < 159; i++) {
		drawLine(bmp, i, i + 20, bmp->bmpWidth - 1 - i, i + 20, 0);
	}
}

/*
 * Draw vertical lines.
 */
void linesV(bitmap *bmp) {
	uchar i;
	bannerBmp(bmp, " Optimized vertical lines ");
	for (i = 10; i < bmp->bmpHeight - 1; i++) {
		drawLine(bmp, i + 57, 10, i + 57, i + 1, 1);
	}
	waitKey(bmp);
	for (i = 10; i < bmp->bmpHeight - 1; i++) {
		drawLine(bmp, i + 57, 10, i + 57, i + 1, 0);
	}
}

/*
 * Draw Bezier curves.
 */
void bezier(bitmap *bmp) {
	uchar i;
	bannerBmp(bmp, " Bezier curves ");
	for (i = 0; i < 35; i++) {
		drawBezier(bmp, i * 5, 10, bmp->bmpWidth - 1, 15 + i * 5,
				bmp->bmpWidth - 1, 15 + i * 5, 1);
	}
	waitKey(bmp);
	for (i = 0; i < 35; i++) {
		drawBezier(bmp, i * 5, 10, bmp->bmpWidth - 1, 15 + i * 5,
				bmp->bmpWidth - 1, 15 + i * 5, 0);
	}
}

/*
 * Draw rectangles.
 */
void rectangles(bitmap *bmp) {
	uchar i;
	bannerBmp(bmp, " Rectangles ");
	for (i = 1; i < 30; i++) {
		drawRect(bmp, i * 2, i * 2, (i * 10) + 20, (i * 5) + 20, 1);
	}
	waitKey(bmp);
	for (i = 1; i < 30; i++) {
		drawRect(bmp, i * 2, i * 2, (i * 10) + 20, (i * 5) + 20, 0);
	}
}

/*
 * Draw squares.
 */
void squares(bitmap *bmp) {
	uchar i;
	bannerBmp(bmp, " Squares ");
	for (i = 0; i < 10; i++) {
		drawSquare(bmp, i * 8, i * 8, (i * 8) + 8, 1);
	}
	waitKey(bmp);
	for (i = 0; i < 10; i++) {
		drawSquare(bmp, i * 8, i * 8, (i * 8) + 8, 0);
	}
}

/*
 * Draw ellipses.
 */
void ellipses(bitmap *bmp) {
	ushort i;
	bannerBmp(bmp, " Ellipses ");
	for (i = 1; i < 9; i++) {
		drawEllipse(bmp, 159, 99, i * 19, i * 10, 1);
	}
	waitKey(bmp);
	for (i = 1; i < 9; i++) {
		drawEllipse(bmp, 159, 99, i * 19, i * 10, 0);
	}
}

/*
 * Draw circles.
 */
void circles(bitmap *bmp) {
	ushort i;
	bannerBmp(bmp, " Circles ");
	for (i = 1; i < 12; i++) {
		drawCircle(bmp, 159, 99, i * 10, 1);
	}
	waitKey(bmp);
	for (i = 1; i < 12; i++) {
		drawCircle(bmp, 159, 99, i * 10, 0);
	}
}

/*
 * Run demo.
 */
void run(bitmap *bmp, uchar *vicMem) {
	char str[40];
	(bmp->printBmp)(bmp, 0, 0, "This demo will show off bitmap graphics."
			"Interrupts are disabled and getKey is   "
			"used to read keyboard.                  ");
	sprintf(str, "mem: %04x", vicMem);
	(bmp->printBmp)(bmp, 0, 4, str);
	sprintf(str, "chr: %04x", bmp->bmpChrMem);
	(bmp->printBmp)(bmp, 0, 6, str);
	sprintf(str, "col: %04x", bmp->bmpColMem);
	(bmp->printBmp)(bmp, 0, 8, str);
	sprintf(str, "bmp: %04x", bmp->bmpMem);
	(bmp->printBmp)(bmp, 0, 10, str);
	waitKey(bmp);
	clearBitmap(bmp);
	lines(bmp);
	clearBitmap(bmp);
	linesH(bmp);
	clearBitmap(bmp);
	linesV(bmp);
	clearBitmap(bmp);
	bezier(bmp);
	clearBitmap(bmp);
	rectangles(bmp);
	clearBitmap(bmp);
	squares(bmp);
	clearBitmap(bmp);
	ellipses(bmp);
	clearBitmap(bmp);
	circles(bmp);
}

main() {
	/* We need to use bank 1 since program is close to 16K */
	uchar *vicMem = allocVicMem(1);
	/* Create bitmap struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	/* Save border/background color */
	uchar border = inp(vicBorderCol);
	uchar background = inp(vicBgCol0);
	init(bmp);
	run(bmp, vicMem);
	done(border, background);
	/* Free memory */
	free(vicMem);
	free(bmp);
}
