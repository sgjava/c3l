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
typedef void (*setPixelPtr)(bitmap*, unsigned int, unsigned int, unsigned char);
typedef void (*clearBmpPtr)(bitmap*, unsigned char);
typedef void (*clearBmpColPtr)(bitmap*, unsigned char);
typedef void (*drawLineHPtr)(bitmap*, unsigned int, unsigned int, unsigned int, unsigned char);
typedef void (*drawLineVPtr)(bitmap*, unsigned int, unsigned int, unsigned int, unsigned char);
typedef void (*printBmpPtr)(bitmap*, unsigned char, unsigned char, char*);
typedef void (*printBmpColPtr)(bitmap*, unsigned char, unsigned char, unsigned char, char*);

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

extern void __LIB__ drawLine(bitmap *bmp, int x0, int y0, int x1, int y1, unsigned char color);
extern void __LIB__ drawBezier(bitmap *bmp, int x0, int y0, int x1, int y1, int x2,
		int y2, unsigned char color);
extern void __LIB__ drawEllipse(bitmap *bmp, int xc, int yc, int a, int b, unsigned char color);
extern void __LIB__ drawCircle(bitmap *bmp, int xc, int yc, int a, unsigned char color);
extern void __LIB__ drawRect(bitmap *bmp, int x, int y, int w, int h, unsigned char color);
extern void __LIB__ drawSquare(bitmap *bmp, int x, int y, int len, unsigned char color);

#endif
