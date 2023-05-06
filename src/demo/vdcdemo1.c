/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cia.h"
#include "vdc.h"
#include "hitech.h"
#include <sys.h>

/*
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void init(screen *scr, uchar *chr) {
	initCia();
	initVdcBmp(scr, vdcScrMem, vdcColMem, chr, vdcBlack, vdcWhite, vdcBlack);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done(screen *scr, uchar *chr) {
	doneVdc();
	doneCia();
	/* Copy character set from memory to VDC */
	copyVdcMemChr(chr, 0x2000, 512);
}

/*
 * Wait for Return.
 */
void waitKey(screen *scr) {
	printVdcBmp(scr, 0, 24, " Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	printVdcBmp(scr, 0, 24, " Erasing pixels ");
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
	for (i = 0; i < 32; i++) {
		drawLine(scr, 0, 0, i * 20, scr->bmpHeight-1, 1);
		drawLine(scr, scr->bmpWidth-1, 0, scr->bmpWidth-1 - (i * 20), scr->bmpHeight-1, 1);
	}
	waitKey(scr);
	for (i = 0; i < 32; i++) {
		drawLine(scr, 0, 0, i * 20, scr->bmpHeight-1, 0);
		drawLine(scr, scr->bmpWidth-1, 0, scr->bmpWidth-1 - (i * 20), scr->bmpHeight-1, 0);
	}
}

/*
 * Draw horizontal lines.
 */
void linesH(screen *scr) {
	uchar i;
	bannerBmp(scr, " Optimized horizontal lines ");
	/* Use optimized horizontal lines */
	for (i = 0; i < scr->bmpHeight-40; i++) {
		drawLine(scr, i, i + 20, scr->bmpWidth-1 - i, i + 20, 1);
	}
	waitKey(scr);
	for (i = 0; i < scr->bmpHeight-40; i++) {
		drawLine(scr, i, i + 20, scr->bmpWidth-1 - i, i + 20, 0);
	}
}

/*
 * Draw vertical lines.
 */
void linesV(screen *scr) {
	uchar i;
	bannerBmp(scr, " Optimized vertical lines ");
	for (i = 10; i < scr->bmpHeight-1; i++) {
		drawLine(scr, i + 114, 10, i + 114, i + 1, 1);
	}
	waitKey(scr);
	for (i = 10; i < scr->bmpHeight-1; i++) {
		drawLine(scr, i + 114, 10, i + 114, i + 1, 0);
	}
}

/*
 * Draw Bezier curves.
 */
void bezier(screen *scr) {
	uchar i;
	bannerBmp(scr, " Bezier curves ");
	for (i = 0; i < 35; i++) {
		drawBezier(scr, i * 5, 10, scr->bmpWidth-1, 15 + i * 5, scr->bmpWidth-1, 15 + i * 5, 1);
	}
	waitKey(scr);
	for (i = 0; i < 35; i++) {
		drawBezier(scr, i * 5, 10, scr->bmpWidth-1, 15 + i * 5, scr->bmpWidth-1, 15 + i * 5, 0);
	}
}

/*
 * Draw rectangles.
 */
void rectangles(screen *scr) {
	uchar i;
	bannerBmp(scr, " Rectangles ");
	for (i = 1; i < 30; i++) {
		drawRect(scr, i * 2, i * 2, (i * 20) + 20, (i * 5) + 20, 1);
	}
	waitKey(scr);
	for (i = 1; i < 30; i++) {
		drawRect(scr, i * 2, i * 2, (i * 20) + 20, (i * 5) + 20, 0);
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
		drawEllipse(scr, 319, 99, i * 39, i * 10, 1);
	}
	waitKey(scr);
	for (i = 1; i < 9; i++) {
		drawEllipse(scr, 319, 99, i * 39, i * 10, 0);
	}
}

/*
 * Draw circles.
 */
void circles(screen *scr) {
	ushort i;
	bannerBmp(scr, " Circles ");
	for (i = 1; i < 10; i++) {
		drawCircle(scr, 319, 99, i * 20, 1);
	}
	waitKey(scr);
	for (i = 1; i < 10; i++) {
		drawCircle(scr, 319, 99, i * 20, 0);
	}
}

/*
 * Run demo.
 */
void run(screen *scr) {
	lines(scr);
	(scr->clearBmp)(scr, 0);
	linesH(scr);
	(scr->clearBmp)(scr, 0);
	linesV(scr);
	(scr->clearBmp)(scr, 0);
	bezier(scr);
	(scr->clearBmp)(scr, 0);
	rectangles(scr);
	(scr->clearBmp)(scr, 0);
	squares(scr);
	(scr->clearBmp)(scr, 0);
	ellipses(scr);
	(scr->clearBmp)(scr, 0);
	circles(scr);

}

main() {
	/* Save both VDC char sets */
	uchar *chr = (uchar*) malloc(4096);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	init(scr, chr);
	run(scr);
	done(scr, chr);
	/* Free memory */
	free(chr);
	free(scr);
}
