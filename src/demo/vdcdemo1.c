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
#include <cia.h>
#include <vdc.h>
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
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void init(screen *scr, uchar *chr) {
	initCia();
	saveVdc();
	/* Turn off cursor for bitmap mode */
	setVdcCursor(0, 0, vdcCurNone);
	/* Copy VDC char sets to VIC mem */
	copyVdcChrMem(chr, 0x2000, 512);
	/* VDC Screen configuration */
	scr->bmpChrMem = (uchar*) ((ushort) chr) + 0x0800;
	scr->bmpColMem = (uchar*) vdcColMem;
	scr->bmpMem = (uchar*) vdcScrMem;
	scr->bmpWidth = 640;
	scr->bmpHeight = 200;
	scr->bmpSize = ((ulong) scr->bmpWidth * scr->bmpHeight) / 8;
	scr->scrWidth = 80;
	scr->scrHeight = 25;
	scr->bmpColSize = scr->scrWidth * scr->scrHeight;
	scr->aspectRatio = 3;
	scr->clearBmp = clearVdcBmp;
	scr->clearBmpCol = clearVdcBmpCol;
	scr->setPixel = setVdcPix;
	scr->drawLineH = drawVdcLineH;
	scr->drawLineV = drawVdcLineV;
	scr->printBmp = printVdcBmp;
	/* Set bitmap mode */
	setVdcFgBg(15, 0);
	setVdcAttrsOff();
	setVdcBmpMode((ushort) scr->bmpMem, (ushort) scr->bmpColMem);
	(scr->clearBmp)(scr, 0);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done(screen *scr, uchar *chr) {
	restoreVdc();
	/* Copy character set from memory to VDC */
	copyVdcMemChr(chr, 0x2000, 512);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, ciaEnableIrq);
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
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
