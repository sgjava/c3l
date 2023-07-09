/*
 * C128 CP/M graphics demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

/*
 * Wait for Return.
 */
void bitmapWaitKey(bitmap *bmp) {
	(bmp->printBmp)(bmp, 0, bmp->scrHeight - 1, " Press Return ");
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
 * Draw box with label.
 */
void drawBox(bitmap *bmp, int x, int y, int w, int h, char *str) {
	/* Bitmap printing uses same coordinates as character mode */
	(bmp->printBmp)(bmp, x / 8, (y - 8) / 8, str);
	drawRect(bmp, x, y, w, h, 1);
}

/*
 * Draw lines.
 */
void lines(bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	drawBox(bmp, x, y, w, h, "Bresenham");
	for (i = 0; i < count; i++) {
		drawLine(bmp, x + 2, rand() % (h - 4) + y + 2, x + w - 3,
				rand() % (h - 4) + y + 2, 1);
	}
}

/*
 * Draw horizontal lines.
 */
void horzLines(bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	ushort y0;
	drawBox(bmp, x, y, w, h, "Horz lines");
	for (i = 0; i < count; i++) {
		y0 = rand() % (h - 4) + y + 2;
		drawLine(bmp, x + 2, y0, x + w - 3, y0, 1);
	}
}

/*
 * Draw vertical lines.
 */
void vertLines(bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	ushort x0;
	drawBox(bmp, x, y, w, h, "Vert lines");
	for (i = 0; i < count; i++) {
		x0 = rand() % (w - 4) + x + 2;
		drawLine(bmp, x0, y + 2, x0, y + h - 3, 1);
	}
}

/*
 * Draw Bezier.
 */
void bezier(bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	drawBox(bmp, x, y, w, h, "Bezier");
	for (i = 0; i < count; i++) {
		drawBezier(bmp, (i * 2) + x + 2, y + 2, x + (w / 2), (i * 3) + y, x + w - 2,
				(i * 4) + y, 1);
	}
}

/*
 * Draw rectangles.
 */
void rectangles(bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	ushort x0, y0, w0, h0;
	drawBox(bmp, x, y, w, h, "Rectangles");
	for (i = 0; i < count; i++) {
		w0 = rand() % (w - 10) + 5;
		h0 = rand() % (h - 10) + 5;
		x0 = rand() % (w - w0 - 3) + x + 2;
		y0 = rand() % (h - h0 - 3) + y + 2;
		drawRect(bmp, x0, y0, w0, h0, 1);
	}
}

/*
 * Draw squares.
 */
void squares(bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	ushort x0, y0, len;
	drawBox(bmp, x, y, w, h, "Squares");
	for (i = 0; i < count; i++) {
		len = rand() % (h - 12) + 5;
		x0 = rand() % (w - len - 2) + x + 2;
		y0 = rand() % (h - len - 2) + y + 2;
		drawSquare(bmp, x0, y0, len, 1);
	}
}

/*
 * Draw ellipses.
 */
void ellipses(bitmap *bmp, int x, int y, int w, int h, uchar count) {
	uchar i;
	ushort x0, y0, a, b;
	drawBox(bmp, x, y, w, h, "Ellipses");
	for (i = 0; i < count; i++) {
		a = rand() % (w / 2 - 25) + 5;
		b = rand() % (h / 2 - 20) + 5;
		x0 = rand() % (w / 2) + x + 20;
		y0 = rand() % (h / 2) + y + 15;
		drawEllipse(bmp, x0, y0, a, b, 1);
	}
}

/*
 * Run graphics demo.
 */
void runGraphDemo(bitmap *bmp) {
	/* Calc 3x3 matrix using char layout since bitmap printing aligns to char mode boundaries */
	ushort xSize = (bmp->scrWidth / 3) * 8 - 8;
	ushort ySize = (bmp->scrHeight / 3) * 8 - 9;
	ushort x = 0, y = 8;
	srand(inp(vicRaster));
	lines(bmp, x, y, xSize, ySize, 10);
	horzLines(bmp, x += xSize + 8, y, xSize, ySize, 10);
	vertLines(bmp, x += xSize + 8, y, xSize, ySize, 10);
	x = 0;
	y = ySize + 17;
	bezier(bmp, x, y, xSize, ySize, 14);
	rectangles(bmp, x += xSize + 8, y, xSize, ySize, 10);
	squares(bmp, x += xSize + 8, y, xSize, ySize, 50);
	x = 0;
	y += ySize + 9;
	ellipses(bmp, x += xSize + 8, y, xSize, ySize, 50);
	bitmapWaitKey(bmp);
}
