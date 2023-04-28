/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <string.h>
#include <vdc.h>
#include "hitech.h"

/*
 * Print with color.
 */
void printVdcCol(screen *scr, uchar x, uchar y, uchar color, char *str) {
	fillVdcMem((uchar*) (y * scr->scrWidth) + (ushort) scr->scrColMem + x, strlen(str),
			color);
	printVdc(scr, x, y, str);
}
