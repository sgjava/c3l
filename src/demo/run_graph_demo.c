/*
 * C128 CP/M graphics demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <stdlib.h>
#include <vic.h>
#include <demo.h>

/*
 * Wait for Return.
 */
void bitmapWaitKey(const bitmap *bmp) {
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
void drawBox(const bitmap *bmp, const int x, const int y,const  int w, const int h, const char *str) {
	/* Bitmap printing uses same coordinates as character mode */
	(bmp->printBmp)(bmp, x / 8, (y - 8) / 8, str);
	drawRect(bmp, x, y, w, h, bmpWhite);
}

/*
 * Draw lines.
 */
void lines(const bitmap *bmp, const int x, const int y,const  int w, const int h, const unsigned char count) {
	unsigned char i;
	drawBox(bmp, x, y, w, h, "Bresenham");
	for (i = 0; i < count; i++) {
		drawLine(bmp, x + 2, rand() % (h - 4) + y + 2, x + w - 3,
				rand() % (h - 4) + y + 2, bmpWhite);
	}
}

/*
 * Draw horizontal lines.
 */
void horzLines(const bitmap *bmp, const int x, const int y,const  int w, const int h, const unsigned char count) {
	unsigned char i;
	int y0;
	drawBox(bmp, x, y, w, h, "Horz lines");
	for (i = 0; i < count; i++) {
		y0 = rand() % (h - 4) + y + 2;
		drawLine(bmp, x + 2, y0, x + w - 3, y0, bmpWhite);
	}
}

/*
 * Draw vertical lines.
 */
void vertLines(const bitmap *bmp, const int x,const  int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
	int x0;
	drawBox(bmp, x, y, w, h, "Vert lines");
	for (i = 0; i < count; i++) {
		x0 = rand() % (w - 4) + x + 2;
		drawLine(bmp, x0, y + 2, x0, y + h - 3, bmpWhite);
	}
}

/*
 * Draw Bezier.
 */
void bezier(const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
	drawBox(bmp, x, y, w, h, "Bezier");
	for (i = 0; i < count; i++) {
		drawBezier(bmp, (i * 2) + x + 3, y + 3, x + (w / 2), (i * 3) + y,
				x + w - 3, (i * 4) + y, bmpWhite);
	}
}

/*
 * Draw rectangles.
 */
void rectangles(const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
	int x0, y0, w0, h0;
	drawBox(bmp, x, y, w, h, "Rectangles");
	for (i = 0; i < count; i++) {
		w0 = rand() % (w - 10) + 5;
		h0 = rand() % (h - 10) + 5;
		x0 = rand() % (w - w0 - 3) + x + 2;
		y0 = rand() % (h - h0 - 3) + y + 2;
		drawRect(bmp, x0, y0, w0, h0, bmpWhite);
	}
}

/*
 * Draw squares.
 */
void squares(const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
	int x0, y0, len;
	drawBox(bmp, x, y, w, h, "Squares");
	for (i = 0; i < count; i++) {
		len = rand() % 20 + 10;
		x0 = rand() % (w - len - 2) + x + 2;
		y0 = rand() % (h - len - 2) + y + 2;
		drawSquare(bmp, x0, y0, len, bmpWhite);
	}
}

/*
 * Draw ellipses.
 */
void ellipses(const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
	int x0, y0, a, b;
	drawBox(bmp, x, y, w, h, "Ellipses");
	for (i = 0; i < count; i++) {
		a = rand() % 10 + 10;
		b = rand() % 8 + 10;
		x0 = rand() % (w / 4) + (w / 3) + x + 5;
		y0 = rand() % (h / 2) + y + 15;
		drawEllipse(bmp, x0, y0, a, b, bmpWhite);
	}
}

/*
 * Draw circles.
 */
void circles(const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i;
	int x0, y0, len;
	drawBox(bmp, x, y, w, h, "Circles");
	for (i = 0; i < count; i++) {
		len = rand() % (h / 5) + 10;
		x0 = rand() % (w / 3) + (w / 3) + x + 5;
		y0 = rand() % (h / 2) + y + 15;
		drawCircle(bmp, x0, y0, len, bmpWhite);
	}
}

/*
 * Run graphics demo.
 */
void runGraphDemo(const bitmap *bmp) {
	/* Calc 3x3 matrix using char layout since bitmap printing aligns to char mode boundaries */
	unsigned int xSize = (bmp->scrWidth / 3) * 8 - 8;
	unsigned int ySize = (bmp->scrHeight / 3) * 8 - 9;
	unsigned int x = 0, y = 8;
	srand(inp(vicRaster));
	lines(bmp, x, y, xSize, ySize, 10);
	horzLines(bmp, x += xSize + 8, y, xSize, ySize, 10);
	vertLines(bmp, x += xSize + 8, y, xSize, ySize, 10);
	x = 0;
	y = ySize + 17;
	bezier(bmp, x, y, xSize, ySize, 14);
	rectangles(bmp, x += xSize + 8, y, xSize, ySize, 10);
	squares(bmp, x += xSize + 8, y, xSize, ySize, 10);
	x = 0;
	y += ySize + 9;
	ellipses(bmp, x, y, xSize, ySize, 10);
	circles(bmp, x += xSize + 8, y, xSize, ySize, 10);
	bitmapWaitKey(bmp);
}
