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

#include <sys/compiler.h>

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
typedef void (*setPixelPtr)(const bitmap*, const unsigned int, const unsigned int, const unsigned char);
typedef void (*clearBmpPtr)(const bitmap*, const unsigned char);
typedef void (*clearBmpColPtr)(const bitmap*, const unsigned char);
typedef void (*drawLineHPtr)(const bitmap*, const unsigned int, const unsigned int, const unsigned int, const unsigned char);
typedef void (*drawLineVPtr)(const bitmap*, const unsigned int, const unsigned int, const unsigned int, const unsigned char);
typedef void (*printBmpPtr)(const bitmap*, const unsigned char, const unsigned char, const char*);
typedef void (*printBmpColPtr)(const bitmap*, const unsigned char, const unsigned char, const unsigned char, const char*);

/*
 * We treat the bitmap struct like an object and encapsulate member variables and function pointers that allow polymorphism.
 */
typedef struct bitmap {
	/*
	 * Color mapping
	 */
	unsigned char color[16];
	/*
	 * Screen width in characters.
	 */
	unsigned char scrWidth;
	/*
	 * Screen height in characters.
	 */
	unsigned char scrHeight;
	/*
	 * Screen width in pixels.
	 */
	unsigned int bmpWidth;
	/*
	 * Screen height in pixels.
	 */
	unsigned int bmpHeight;
	/*
	 * Bitmap size in bytes.
	 */
	unsigned int bmpSize;
	/*
	 * Bitmap memory location.
	 */
	unsigned char *bmpMem;
	/*
	 * Bitmap color location.
	 */
	unsigned char *bmpColMem;
	/*
	 * Bitmap color size.
	 */
	unsigned int bmpColSize;
	/*
	 * Bitmap character set location.
	 */
	unsigned char *bmpChrMem;
	/*
	 * Aspect ratio multiplier used by circle and square functions.
	 */
	unsigned char aspectRatioMul;
	/*
	 * Aspect ratio divisor used by circle and square functions.
	 */
	unsigned char aspectRatioDiv;
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

extern void __LIB__ drawLine(const bitmap *bmp, const int x0, const int y0, const int x1, const int y1, const unsigned char color);
extern void __LIB__ drawBezier(const bitmap *bmp, const int x0, const int y0, const int x1, const int y1, const int x2, const int y2, const unsigned char color);
extern void __LIB__ drawEllipse(const bitmap *bmp, const int xc, const int yc, const int a, const int b,const  unsigned char color);
extern void __LIB__ drawCircle(const bitmap *bmp, const int xc, const int yc, const int a, const unsigned char color);
extern void __LIB__ drawRect(const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char color);
extern void __LIB__ drawSquare(const bitmap *bmp, const int x, const int y, const int len, const unsigned char color);

#endif
