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
#include <sys.h>
#include <hitech.h>
#include <cia.h>
#include <vdc.h>
#include <screen.h>
#include <graphics.h>

/*
 * Set screen color, screen memory and char set memory.
 * Clear screen and color memory then enable screen.
 */
void init(uchar *chr) {
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
	saveVdc();
	setVdcCursor(0, 0, vdcCurNone);
	/* Copy VDC char sets to VIC mem */
	copyVdcChrMem(chr, 0x2000, 512);
	setVdcFgBg(15, 0);
	setVdcAttrsOff();
	setVdcBmpMode((ushort) bmpMem, (ushort) bmpColMem);
	clearBmp(0);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done(uchar *chr) {
	restoreVdc();
	copyVdcMemChr(chr, 0x2000, 512);
	free(chr);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, 0x82);
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
}

/*
 * Wait for Return.
 */
void waitKey() {
	printVdcBmp(0, 24, " Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	printVdcBmp(0, 24, " Erasing pixels ");
}

/*
 * Print centered text on top line in bitmap.
 */
void bannerBmp(char *str) {
	printVdcBmp(((80 - strlen(str)) >> 1), 0, str);
}

/*
 * Draw lines.
 */
void lines() {
	uchar i;
	bannerBmp(" Bresenham lines ");
	for (i = 0; i < 32; i++) {
		drawLine(0, 0, i * 20, 199, 1);
		drawLine(639, 0, 639 - (i * 20), 199, 1);
	}
	waitKey();
	for (i = 0; i < 32; i++) {
		drawLine(0, 0, i * 20, 199, 0);
		drawLine(639, 0, 639 - (i * 20), 199, 0);
	}
}

/*
 * Draw horizontal lines.
 */
void linesH() {
	uchar i;
	bannerBmp(" Optimized horizontal lines ");
	/* Use optimized horizontal lines */
	for (i = 0; i < 159; i++) {
		drawLine(i, i + 20, 639 - i, i + 20, 1);
	}
	waitKey();
	for (i = 0; i < 159; i++) {
		drawLine(i, i + 20, 639 - i, i + 20, 0);
	}
}

/*
 * Draw vertical lines.
 */
void linesV() {
	uchar i;
	bannerBmp(" Optimized vertical lines ");
	for (i = 10; i < 199; i++) {
		drawLine(i + 114, 10, i + 114, i + 1, 1);
	}
	waitKey();
	for (i = 10; i < 199; i++) {
		drawLine(i + 114, 10, i + 114, i + 1, 0);
	}
}

/*
 * Draw Bezier curves.
 */
void bezier() {
	uchar i;
	bannerBmp(" Bezier curves ");
	for (i = 0; i < 35; i++) {
		drawBezier(i * 5, 10, 639, 15 + i * 5, 639, 15 + i * 5, 1);
	}
	waitKey();
	for (i = 0; i < 35; i++) {
		drawBezier(i * 5, 10, 639, 15 + i * 5, 639, 15 + i * 5, 0);
	}
}

/*
 * Draw rectangles.
 */
void rectangles() {
	uchar i;
	bannerBmp(" Rectangles ");
	for (i = 1; i < 30; i++) {
		drawRect(i * 2, i * 2, (i * 20) + 20, (i * 5) + 20, 1);
	}
	waitKey();
	for (i = 1; i < 30; i++) {
		drawRect(i * 2, i * 2, (i * 20) + 20, (i * 5) + 20, 0);
	}
}

/*
 * Draw squares.
 */
void squares() {
	uchar i;
	bannerBmp(" Squares ");
	for (i = 0; i < 10; i++) {
		drawSquare(i * 8, i * 8, (i * 8) + 8, 1);
	}
	waitKey();
	for (i = 0; i < 10; i++) {
		drawSquare(i * 8, i * 8, (i * 8) + 8, 0);
	}
}

/*
 * Draw ellipses.
 */
void ellipses() {
	ushort i;
	bannerBmp(" Ellipses ");
	for (i = 1; i < 9; i++) {
		drawEllipse(319, 99, i * 39, i * 10, 1);
	}
	waitKey();
	for (i = 1; i < 9; i++) {
		drawEllipse(319, 99, i * 39, i * 10, 0);
	}
}

/*
 * Draw circles.
 */
void circles() {
	ushort i;
	bannerBmp(" Circles ");
	for (i = 1; i < 10; i++) {
		drawCircle(319, 99, i * 20, 1);
	}
	waitKey();
	for (i = 1; i < 10; i++) {
		drawCircle(319, 99, i * 20, 0);
	}
}

/*
 * Run demo.
 */
void run() {
	lines();
	clearBmp(0);
	linesH();
	clearBmp(0);
	linesV();
	clearBmp(0);
	bezier();
	clearBmp(0);
	rectangles();
	clearBmp(0);
	squares();
	clearBmp(0);
	ellipses();
	clearBmp(0);
	circles();

}

main() {
	/* We use pointer to be compatible with VIC */
	uchar *bmp = (uchar*) 0x0000;
	/* Save both VDC char sets */
	uchar *chr = (uchar*) malloc(4096);
	/* Use alternate character set */
	uchar *altChr = (uchar*) ((ushort) chr) + 0x0800;
	/* Set default sizes and locations */
	bmpWidth = 640;
	bmpHeight = 200;
	bmpSize = ((ulong) bmpWidth * bmpHeight) / 8;
	scrWidth = 80;
	scrHeight = 25;
	bmpColSize = scrWidth * scrHeight;
	bmpMem = bmp;
	bmpColMem = (uchar*) vdcColMem;
	bmpChrMem = altChr;
	/* Use VDC clear functions */
	clearBmp = clearVdcBmp;
	clearBmpCol = clearVdcBmpCol;
	/* Use VDC pixel functions */
	setPixel = setVdcPix;
	clearPixel = clearVdcPix;
	/* Use optimized horizontal and vertical lines on the VDC */
	drawLineH = drawVdcLineH;
	drawLineV = drawVdcLineV;
	/* VDC aspect ratio */
	aspectRatio = 3;
	init(chr);
	run();
	done(chr);
}
