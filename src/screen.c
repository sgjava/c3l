/*
 * C128 CP/M text abstraction.
 *
 * Screen abstraction uses function pointers to drive text output, thus the
 * same code will work on the VIC and VDC. Technically this code would work
 * with other displays as well. You just need to implement the functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <string.h>
#include <hitech.h>

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
 * Clear screen.
 */
void (*clearScr)(uchar);

/*
 * Clear screen color.
 */
void (*clearScrCol)(uchar);

/*
 * Print text without color.
 */
void (*print)(uchar, uchar, char *);

/*
 * Print text with color.
 */
void (*printCol)(uchar, uchar, uchar, char *);
