/*
 * C128 CP/M text and graphics abstraction.
 *
 * Screen abstraction uses function pointers to drive output, thus the
 * same code will work on the VIC and VDC. This will also allow for virtual
 * screens, page flipping, etc.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _SCREEN_H
#define _SCREEN_H

#include "hitech.h"

/*
 * Forward reference for function pointer typedefs.
 */
typedef struct screen screen;

/*
 * General function pointers.
 */
typedef void (*fillMemPtr)(uchar*, ushort, uchar);

/*
 * Text function pointers.
 */
typedef void (*clearScrPtr)(screen*, uchar);
typedef void (*clearScrColPtr)(screen*, uchar);
typedef void (*printPtr)(screen*, uchar, uchar, char*);
typedef void (*printColPtr)(screen*, uchar, uchar, uchar, char*);
typedef void (*scrollUpPtr)(screen*, uchar, uchar, uchar, uchar);
typedef void (*scrollUpColPtr)(screen*, uchar, uchar, uchar, uchar);

/*
 * Bitmap function pointers.
 */
typedef void (*setPixelPtr)(screen*, ushort, ushort, uchar);
typedef void (*clearBmpPtr)(screen*, uchar);
typedef void (*clearBmpColPtr)(screen*, uchar);
typedef void (*drawLineHPtr)(screen*, ushort, ushort, ushort, uchar);
typedef void (*drawLineVPtr)(screen*, ushort, ushort, ushort, uchar);
typedef void (*printBmpPtr)(screen*, uchar, uchar, char*);
typedef void (*printBmpColPtr)(screen*, uchar, uchar, uchar, char*);

/*
 * We treat the screen struct like an object and encapsulate member variables and function pointers that allow polymorphism.
 */
typedef struct screen {
	/*
	 * Screen width in characters.
	 */
	uchar scrWidth;
	/*
	 * Screen height in characters.
	 */
	uchar scrHeight;
	/*
	 * Screen size in bytes.
	 */
	ushort scrSize;
	/*
	 * Screen memory location.
	 */
	uchar *scrMem;
	/*
	 * Screen color location.
	 */
	uchar *scrColMem;
	/*
	 * Character set location.
	 */
	uchar *chrMem;
	/*
	 * Fill memory with uchar.
	 */
	fillMemPtr fillMem;
	/*
	 * Clear screen.
	 */
	clearScrPtr clearScr;
	/*
	 * Clear screen color.
	 */
	clearScrColPtr clearScrCol;
	/*
	 * Print text without color.
	 */
	printPtr print;
	/*
	 * Print text with color.
	 */
	printColPtr printCol;
	/*
	 * Scroll text up one line.
	 */
	scrollUpPtr scrollUp;
	/*
	 * Scroll text color one line.
	 */
	scrollUpColPtr scrollUpCol;
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

extern char* asciiToPet(char *str);
extern void drawLine(screen *scr, int x0, int y0, int x1, int y1, uchar color);
extern void drawBezier(screen *scr, int x0, int y0, int x1, int y1, int x2,
		int y2, uchar color);
extern void drawEllipse(screen *scr, int xc, int yc, int a, int b, uchar color);
extern void drawCircle(screen *scr, int xc, int yc, int a, uchar color);
extern void drawRect(screen *scr, int x0, int y0, int x1, int y1, uchar color);
extern void drawSquare(screen *scr, int x, int y, int len, uchar color);

#endif
