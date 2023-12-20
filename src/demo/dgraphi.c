/*
 * C128 CP/M graphics demo for split screen.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <console.h>
#include <hitech.h>
#include <screen.h>
#include <cia.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

#include "demo.h"

/*
 * Set VIC raster interrupt address.
 */
void setVicInt(uchar ras1, uchar ras2, screen *scr, bitmap *bmp) {
	uchar scrMcr, bmpMcr, bmpColMcr, chrMcr, vicBank = (ushort) scr->scrMem
			/ 16384;
	/* From VIC perspective this is only relevant for text mode, but bitmap print routines use same character set */
	chrMcr = (((ushort) scr->chrMem - (vicBank * 16384)) / 2048) << 1;
	/* Setting for screen memory control register */
	scrMcr = (((ushort) scr->scrMem - (vicBank * 16384)) / 1024) << 4;
	/* Setting for bitmap memory control register */
	bmpMcr = (((ushort) bmp->bmpMem - (vicBank * 16384)) / 8192) << 3;
	/* Setting for screen memory control register (used for bitmap color) */
	bmpColMcr = (((ushort) bmp->bmpColMem - (vicBank * 16384)) / 1024) << 4;
	/* Bitmap on top and text on bottom, memory control register and mode bytes packed into ushort */
	vicSplitScr(ras1, (((bmpMcr | bmpColMcr)) << 8) | 0x3b, ras2,
			(((scrMcr | chrMcr)) << 8) | 0x1b);
}

/*
 * Enable VIC raster interrupt address.
 */
void enableVicInt(ushort address) {
	ushort *intVec = (ushort*) 0xfdfe;
#asm
	di
#endasm
	intVec[0] = address;
	/* Ack any previous raster interrupt */
	outp(vicIntFlag, 0xff);
	/* Enable raster interrupt */
	outp(vicIntMask, 0x01);
#asm
	ei
#endasm
}

/*
 * Disable VIC raster interrupt.
 */
void disableVicInt(ushort address) {
	ushort *intVec = (ushort*) 0xfdfe;
#asm
	di
#endasm
	/* Disable raster interrupt */
	outp(vicIntMask, 0x00);
	/* Ack any previous raster interrupt */
	outp(vicIntFlag, 0xff);
	intVec[0] = address;
#asm
	ei
#endasm
}

/*
 * Draw box with label.
 */
void drawBoxI(bitmap *bmp, int x, int y, int w, int h, char *str) {
	/* Bitmap printing uses same coordinates as character mode */
	(bmp->printBmp)(bmp, x / 8, (y - 8) / 8, str);
	drawRect(bmp, x, y, w, h, bmpWhite);
}

/*
 * Draw lines.
 */
void linesI(console *con, bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	int x0, y0, x1, y1;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Bresenham");
	for (i = 0; i < count; i++) {
		x0 = x + 2;
		y0 = rand() % (h - 4) + y + 2;
		x1 = x + w - 3;
		y1 = rand() % (h - 4) + y + 2;
		sprintf(str, "drawLine(%d, %d, %d, %d)", x0, y0, x1, y1);
		printLineCon(con, str);
		drawLine(bmp, x0, y0, x1, y1, bmpWhite);
	}
}

/*
 * Draw horizontal lines.
 */
void horzLinesI(console *con, bitmap *bmp, int x, int y, int w, int h,
uchar count) {
	uchar i;
	int x0, y0, x1;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Horz lines");
	for (i = 0; i < count; i++) {
		x0 = x + 2;
		y0 = rand() % (h - 4) + y + 2;
		x1 = x + w - 3;
		sprintf(str, "drawLine(%d, %d, %d, %d)", x0, y0, x1, y0);
		printLineCon(con, str);
		drawLine(bmp, x0, y0, x1, y0, bmpWhite);
	}
}

/*
 * Draw vertical lines.
 */
void vertLinesI(console *con, bitmap *bmp, int x, int y, int w, int h,
uchar count) {
	uchar i;
	int x0, y0, y1;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Vert lines");
	for (i = 0; i < count; i++) {
		x0 = rand() % (w - 4) + x + 2;
		y0 = y + 2;
		y1 = y + h - 3;
		sprintf(str, "drawLine(%d, %d, %d, %d)", x0, y0, x0, y1);
		printLineCon(con, str);
		drawLine(bmp, x0, y0, x0, y1, bmpWhite);
	}
}

/*
 * Draw Bezier.
 */
void bezierI(console *con, bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	int x0, y0, x1, y1, x2, y2;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Bezier");
	for (i = 0; i < count; i++) {
		x0 = (i * 2) + x + 3;
		y0 = y + 3;
		x1 = x + (w / 2);
		y1 = (i * 3) + y;
		x2 = x + w - 3;
		y2 = (i * 4) + y;
		sprintf(str, "drawBezier(%d, %d, %d, %d, %d, %d)", x0, y0, x1, y1, x2,
				y2);
		printLineCon(con, str);
		drawBezier(bmp, x0, y0, x1, y1, x2, y2, bmpWhite);
	}
}

/*
 * Draw rectangles.
 */
void rectanglesI(console *con, bitmap *bmp, int x, int y, int w, int h,
uchar count) {
	uchar i;
	int x0, y0, w0, h0;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Rectangles");
	for (i = 0; i < count; i++) {
		w0 = rand() % (w - 10) + 5;
		h0 = rand() % (h - 10) + 5;
		x0 = rand() % (w - w0 - 3) + x + 2;
		y0 = rand() % (h - h0 - 3) + y + 2;
		sprintf(str, "drawRect(%d, %d, %d, %d)", x0, y0, w0, h0);
		printLineCon(con, str);
		drawRect(bmp, x0, y0, w0, h0, bmpWhite);
	}
}

/*
 * Draw squares.
 */
void squaresI(console *con, bitmap *bmp, int x, int y, int w, int h,
uchar count) {
	uchar i;
	int x0, y0, len;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Squares");
	for (i = 0; i < count; i++) {
		len = rand() % 20 + 10;
		x0 = rand() % (w - len - 2) + x + 2;
		y0 = rand() % (h - len - 2) + y + 2;
		sprintf(str, "drawSquare(%d, %d, %d)", x0, y0, len);
		printLineCon(con, str);
		drawSquare(bmp, x0, y0, len, bmpWhite);
	}
}

/*
 * Draw ellipses.
 */
void ellipsesI(console *con, bitmap *bmp, int x, int y, int w, int h,
uchar count) {
	uchar i;
	int x0, y0, a, b;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Ellipses");
	for (i = 0; i < count; i++) {
		a = rand() % (w / 5) + (w / 5) - 4;
		b = rand() % (h / 2 - 20) + 5;
		x0 = rand() % (w / 4) + (w / 3) + x + 7;
		y0 = rand() % (h / 2) + y + 15;
		sprintf(str, "drawEllipse(%d, %d, %d, %d)", x0, y0, a, b);
		printLineCon(con, str);
		drawEllipse(bmp, x0, y0, a, b, bmpWhite);
	}
}

/*
 * Draw circles.
 */
void circlesI(console *con, bitmap *bmp, int x, int y, int w, int h,
uchar count) {
	uchar i;
	int x0, y0, len;
	char str[41];
	drawBoxI(bmp, x, y, w, h, "Circles");
	for (i = 0; i < count; i++) {
		len = rand() % (h / 5) + 10;
		x0 = rand() % (w / 3) + (w / 3) + x + 5;
		y0 = rand() % (h / 2) + y + 15;
		sprintf(str, "drawCircle(%d, %d, %d)", x0, y0, len);
		printLineCon(con, str);
		drawCircle(bmp, x0, y0, len, bmpWhite);
	}
}

/*
 * Run graphics demo.
 */
void runGraphDemoI(console *con, bitmap *bmp, ushort code) {
	ushort *intVec = (ushort*) 0xfdfe, address = intVec[0];
	/* Calc 3x3 matrix using char layout since bitmap printing aligns to char mode boundaries */
	ushort xSize = (bmp->scrWidth / 3) * 8 - 8;
	ushort ySize = (bmp->scrHeight / 3) * 8 - 9;
	ushort x = 0, y = 8;
	uchar tens, i;
	con->curY = con->scr->scrHeight - 1;
	setVicInt(0, y + ySize + 50, con->scr, bmp);
	/* New interrupt routine */
	enableVicInt(code);
	srand(inp(vicRaster));
	linesI(con, bmp, x, y, xSize, ySize, 10);
	horzLinesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	vertLinesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	x = 0;
	y = ySize + 17;
	setVicInt(0, y + ySize + 50, con->scr, bmp);
	bezierI(con, bmp, x, y, xSize, ySize, 14);
	rectanglesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	squaresI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	x = 0;
	y += ySize + 9;
	setVicInt(0, y + ySize + 50, con->scr, bmp);
	ellipsesI(con, bmp, x, y, xSize, ySize, 10);
	circlesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	/* Show how we can easily move raster split */
	for (i = 241; i > 42; i -= 8) {
		tens = inp(cia1 + ciaTodTen);
		setVicInt(0, i, con->scr, bmp);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
	}
	for (i = 41; i < 242; i += 8) {
		tens = inp(cia1 + ciaTodTen);
		setVicInt(0, i, con->scr, bmp);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
	}
	waitKey(con->scr);
	/* Disable raster interrupt */
	disableVicInt(address);
}
