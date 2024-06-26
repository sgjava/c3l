/*
 * C128 CP/M graphics demo for split screen.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <console.h>
#include <screen.h>
#include <cia.h>
#include <stdlib.h>
#include <stdio.h>
#include <vic.h>
#include <demo.h>

/*
 * Set VIC raster interrupt address.
 */
void setVicInt(const unsigned char ras1, const unsigned char mode1, const unsigned char ras2, const unsigned char mode2,
		const screen *scr, const bitmap *bmp) {
	unsigned char scrMcr, bmpMcr, bmpColMcr, chrMcr, vicBank = (unsigned int) scr->scrMem / 16384;
	/* From VIC perspective this is only relevant for text mode, but bitmap print routines use same character set */
	chrMcr = (((unsigned int) scr->chrMem - (vicBank * 16384)) / 2048) << 1;
	/* Setting for screen memory control register */
	scrMcr = (((unsigned int) scr->scrMem - (vicBank * 16384)) / 1024) << 4;
	/* Setting for bitmap memory control register */
	bmpMcr = (((unsigned int) bmp->bmpMem - (vicBank * 16384)) / 8192) << 3;
	/* Setting for screen memory control register (used for bitmap color) */
	bmpColMcr = (((unsigned int) bmp->bmpColMem - (vicBank * 16384)) / 1024) << 4;
	if (mode1 == 0x3b) {
		/* Bitmap on top and text on bottom, memory control register and mode bytes packed into unsigned int */
		vicSplitScr(ras1, (((bmpMcr | bmpColMcr)) << 8) | mode1, ras2, (((scrMcr | chrMcr)) << 8) | mode2);
	} else {
		/* Text on top and bitmap on bottom, memory control register and mode bytes packed into unsigned int */
		vicSplitScr(ras1, (((scrMcr | chrMcr)) << 8) | mode1, ras2, (((bmpMcr | bmpColMcr)) << 8) | mode2);
	}
}

/*
 * Enable VIC raster interrupt address.
 */
void enableVicInt(const unsigned int address) {
	unsigned int *intVec = (unsigned int*) 0xfdfe;
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
void disableVicInt(const unsigned int address) {
	unsigned int *intVec = (unsigned int*) 0xfdfe;
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
void drawBoxI(const bitmap *bmp, const int x, const int y, const int w, const int h, const char *str) {
	/* Bitmap printing uses same coordinates as character mode */
	(bmp->printBmp)(bmp, x / 8, (y - 8) / 8, str);
	drawRect(bmp, x, y, w, h, bmpWhite);
}

/*
 * Draw lines.
 */
void linesI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
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
void horzLinesI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h,
		const unsigned char count) {
	unsigned char i;
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
void vertLinesI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h,
		const unsigned char count) {
	unsigned char i;
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
void bezierI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
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
		sprintf(str, "drawBezier(%d, %d, %d, %d, %d, %d)", x0, y0, x1, y1, x2, y2);
		printLineCon(con, str);
		drawBezier(bmp, x0, y0, x1, y1, x2, y2, bmpWhite);
	}
}

/*
 * Draw rectangles.
 */
void rectanglesI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h,
		const unsigned char count) {
	unsigned char i;
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
void squaresI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
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
void ellipsesI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
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
void circlesI(const console *con, const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
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
void runGraphDemoI(const console *con, const bitmap *bmp, const unsigned int code) {
	unsigned int *intVec = (unsigned int*) 0xfdfe, address = intVec[0];
	/* Calc 3x3 matrix using char layout since bitmap printing aligns to char mode boundaries */
	unsigned int xSize = (bmp->scrWidth / 3) * 8 - 8;
	unsigned int ySize = (bmp->scrHeight / 3) * 8 - 9;
	unsigned int x = 0, y = 8;
	unsigned char tens, i;
	con->curY = con->scr->scrHeight - 1;
	setVicInt(0, 0x3b, y + ySize + 50, 0x1b, con->scr, bmp);
	/* New interrupt routine */
	enableVicInt(code);
	srand(inp(vicRaster));
	linesI(con, bmp, x, y, xSize, ySize, 10);
	horzLinesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	vertLinesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	x = 0;
	y = ySize + 17;
	setVicInt(0, 0x3b, y + ySize + 50, 0x1b, con->scr, bmp);
	bezierI(con, bmp, x, y, xSize, ySize, 14);
	rectanglesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	squaresI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	setVicInt(0, 0x1b, y + ySize + 50, 0x3b, con->scr, bmp);
	x = 0;
	y += ySize + 9;
	ellipsesI(con, bmp, x, y, xSize, ySize, 10);
	circlesI(con, bmp, x += xSize + 8, y, xSize, ySize, 10);
	setVicInt(0, 0x3b, 241, 0x1b, con->scr, bmp);
	/* Show how we can easily move raster split */
	for (i = 241; i > 42; i -= 8) {
		tens = inp(cia1 + ciaTodTen);
		setVicInt(0, 0x3b, i, 0x1b, con->scr, bmp);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
	}
	for (i = 41; i < 242; i += 8) {
		tens = inp(cia1 + ciaTodTen);
		setVicInt(0, 0x3b, i, 0x1b, con->scr, bmp);
		/* Wait for tenth of a second to change */
		while (inp(cia1 + ciaTodTen) == tens)
			;
	}
	waitKey(con->scr);
	/* Disable raster interrupt */
	disableVicInt(address);
}
