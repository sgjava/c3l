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

#include <sys/compiler.h>

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
typedef void (*fillMemPtr)(const unsigned char*, const unsigned int, const unsigned char);

/*
 * Text function pointers.
 */
typedef void (*clearScrPtr)(const screen*, const unsigned char);
typedef void (*clearScrColPtr)(const screen*, const unsigned char);
typedef void (*printPtr)(const screen*, const unsigned char, const unsigned char, const char*);
typedef void (*printColPtr)(const screen*, const unsigned char, const unsigned char, const unsigned char, const char*);
typedef void (*scrollUpPtr)(const screen*, const unsigned char, const unsigned char, const unsigned char, const unsigned char);
typedef void (*scrollUpColPtr)(const screen*, const unsigned char, const unsigned char, const unsigned char, const unsigned char);
typedef void (*copyScrToStrPtr)(const screen*, const unsigned int, const char*, const unsigned int);

/*
 * We treat the screen struct like an object and encapsulate member variables and function pointers that allow polymorphism.
 */
typedef struct screen {
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
	 * Screen size in bytes.
	 */
	unsigned int scrSize;
	/*
	 * Screen memory location.
	 */
	unsigned char *scrMem;
	/*
	 * Screen color location.
	 */
	unsigned char *scrColMem;
	/*
	 * Character set location.
	 */
	unsigned char *chrMem;
	/*
	 * Fill memory with unsigned char.
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

extern void __LIB__ asciiToPet(const char *str);

#endif
