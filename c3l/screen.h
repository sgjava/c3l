/*
 * C128 CP/M text abstraction.
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

/* Generic color mapping */
#define scrBlack       0
#define scrWhite       1
#define scrRed         2
#define scrCyan        3
#define scrPurple      4
#define scrGreen       5
#define scrBlue        6
#define scrYellow      7
#define scrOrange      8
#define scrBrown       9
#define scrLightRed   10
#define scrDarkGray   11
#define scrMedGray    12
#define scrLightGreen 13
#define scrLightBlue  14
#define scrLightGray  15

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
typedef void (*copyScrToStrPtr)(screen*, ushort, char*, ushort);

/*
 * We treat the screen struct like an object and encapsulate member variables and function pointers that allow polymorphism.
 */
typedef struct screen {
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
	 * Copy text from screen to string.
	 */
	copyScrToStrPtr copyScrToStr;
};

extern char* asciiToPet(char *str);

#endif
