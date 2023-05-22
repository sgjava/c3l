/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <bitmap.h>
#include <stdlib.h>
#include <string.h>
#include <vdc.h>

/*
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void init(bitmap *bmp, uchar *chr) {
	initCia();
	initVdcBmp(bmp, vdcScrMem, vdcColMem, chr);
	initVdcBmpMode(bmp, chr, vdcBlack, vdcWhite, vdcBlack);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done(bitmap *bmp, uchar *chr) {
	doneVdc();
	doneCia();
	/* Copy character set from memory to VDC */
	copyVdcMemChr(chr, 0x2000, 512);
}

/*
 * Wait for Return.
 */
void waitKey(bitmap *bmp) {
	printVdcBmp(bmp, 0, 24, " Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	printVdcBmp(bmp, 0, 24, " Erasing pixels ");
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
	for (i = 0; i < 32; i++) {
		drawLine(bmp, 0, 0, i * 20, bmp->bmpHeight - 1, 1);
		drawLine(bmp, bmp->bmpWidth - 1, 0, bmp->bmpWidth - 1 - (i * 20),
				bmp->bmpHeight - 1, 1);
	}
	waitKey(bmp);
	for (i = 0; i < 32; i++) {
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
	/* Use optimized horizontal lines */
	for (i = 0; i < bmp->bmpHeight - 40; i++) {
		drawLine(bmp, i, i + 20, bmp->bmpWidth - 1 - i, i + 20, 1);
	}
	waitKey(bmp);
	for (i = 0; i < bmp->bmpHeight - 40; i++) {
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
		drawLine(bmp, i + 114, 10, i + 114, i + 1, 1);
	}
	waitKey(bmp);
	for (i = 10; i < bmp->bmpHeight - 1; i++) {
		drawLine(bmp, i + 114, 10, i + 114, i + 1, 0);
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
		drawRect(bmp, i * 2, i * 2, (i * 20) + 20, (i * 5) + 20, 1);
	}
	waitKey(bmp);
	for (i = 1; i < 30; i++) {
		drawRect(bmp, i * 2, i * 2, (i * 20) + 20, (i * 5) + 20, 0);
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
		drawEllipse(bmp, 319, 99, i * 39, i * 10, 1);
	}
	waitKey(bmp);
	for (i = 1; i < 9; i++) {
		drawEllipse(bmp, 319, 99, i * 39, i * 10, 0);
	}
}

/*
 * Draw circles.
 */
void circles(bitmap *bmp) {
	ushort i;
	bannerBmp(bmp, " Circles ");
	for (i = 1; i < 10; i++) {
		drawCircle(bmp, 319, 99, i * 20, 1);
	}
	waitKey(bmp);
	for (i = 1; i < 10; i++) {
		drawCircle(bmp, 319, 99, i * 20, 0);
	}
}

/*
 * Run demo.
 */
void run(bitmap *bmp) {
	lines(bmp);
	(bmp->clearBmp)(bmp, 0);
	linesH(bmp);
	(bmp->clearBmp)(bmp, 0);
	linesV(bmp);
	(bmp->clearBmp)(bmp, 0);
	bezier(bmp);
	(bmp->clearBmp)(bmp, 0);
	rectangles(bmp);
	(bmp->clearBmp)(bmp, 0);
	squares(bmp);
	(bmp->clearBmp)(bmp, 0);
	ellipses(bmp);
	(bmp->clearBmp)(bmp, 0);
	circles(bmp);
}

main() {
	/* Save both VDC char sets */
	uchar *chr = (uchar*) malloc(4096);
	/* Create screen struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	init(bmp, chr);
	run(bmp);
	done(bmp, chr);
	/* Free memory */
	free(chr);
	free(bmp);
}
