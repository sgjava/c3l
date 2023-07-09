/*
 * C128 CP/M graphics abstraction.
 *
 * Bitmap abstraction uses function pointers to drive output, thus the
 * same code will work on the VIC and VDC. This will also allow for virtual
 * screens, page flipping, etc.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _BITMAP_H
#define _BITMAP_H

#include "hitech.h"

/* Generic color mapping */
#define bmpBlack       0
#define bmpWhite       1
#define bmpRed         2
#define bmpCyan        3
#define bmpPurple      4
#define bmpGreen       5
#define bmpBlue        6
#define bmpYellow      7
#define bmpOrange      8
#define bmpBrown       9
#define bmpLightRed   10
#define bmpDarkGray   11
#define bmpMedGray    12
#define bmpLightGreen 13
#define bmpLightBlue  14
#define bmpLightGray  15

/*
 * Forward reference for function pointer typedefs.
 */
typedef struct bitmap bitmap;

/*
 * Bitmap function pointers.
 */
typedef void (*setPixelPtr)(bitmap*, ushort, ushort, uchar);
typedef void (*clearBmpPtr)(bitmap*, uchar);
typedef void (*clearBmpColPtr)(bitmap*, uchar);
typedef void (*drawLineHPtr)(bitmap*, ushort, ushort, ushort, uchar);
typedef void (*drawLineVPtr)(bitmap*, ushort, ushort, ushort, uchar);
typedef void (*printBmpPtr)(bitmap*, uchar, uchar, char*);
typedef void (*printBmpColPtr)(bitmap*, uchar, uchar, uchar, char*);

/*
 * We treat the bitmap struct like an object and encapsulate member variables and function pointers that allow polymorphism.
 */
typedef struct bitmap {
	/*
	 * Color mapping
	 */
	uchar color[16];
	/*
	 * Screen width in characters.
	 */
	uchar scrWidth;
	/*
	 * Screen height in characters.
	 */
	uchar scrHeight;
	/*
	 * Screen width in pixels.
	 */
	ushort bmpWidth;
	/*
	 * Screen height in pixels.
	 */
	ushort bmpHeight;
	/*
	 * Bitmap size in bytes.
	 */
	ushort bmpSize;
	/*
	 * Bitmap memory location.
	 */
	uchar *bmpMem;
	/*
	 * Bitmap color location.
	 */
	uchar *bmpColMem;
	/*
	 * Bitmap color size.
	 */
	ushort bmpColSize;
	/*
	 * Bitmap character set location.
	 */
	uchar *bmpChrMem;
	/*
	 * Aspect ratio used by circle and square functions.
	 */
	uchar aspectRatio;
	/*
	 * Set pixel.
	 */
	setPixelPtr setPixel;
	/*
	 * Clear bitmap.
	 */
	clearBmpPtr clearBmp;
	/*
	 * Clear bitmap color.
	 */
	clearBmpColPtr clearBmpCol;
	/*
	 * Draw horizontal line.
	 */
	drawLineHPtr drawLineH;
	/*
	 * Draw vertical line.
	 */
	drawLineVPtr drawLineV;
	/*
	 * Print bitmap text without color.
	 */
	printBmpPtr printBmp;
	/*
	 * Print bitmap text with color.
	 */
	printBmpColPtr printBmpCol;
};

extern void drawLine(bitmap *bmp, int x0, int y0, int x1, int y1, uchar color);
extern void drawBezier(bitmap *bmp, int x0, int y0, int x1, int y1, int x2,
		int y2, uchar color);
extern void drawEllipse(bitmap *bmp, int xc, int yc, int a, int b, uchar color);
extern void drawCircle(bitmap *bmp, int xc, int yc, int a, uchar color);
extern void drawRect(bitmap *bmp, int x, int y, int w, int h, uchar color);
extern void drawSquare(bitmap *bmp, int x, int y, int len, uchar color);

#endif
