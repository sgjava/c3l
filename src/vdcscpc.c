/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <string.h>
#include <screen.h>
#include <vdc.h>
#include "hitech.h"

/*
 * Print with color.
 */
void printVdcCol(uchar x, uchar y, uchar color, char *str) {
	fillVdcMem((y * scrWidth) + (ushort) scrColMem + x, strlen(str), color);
	printVdc(x, y, str);
}
