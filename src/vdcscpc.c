/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <string.h>
#include <vdc.h>

/*
 * Print with color.
 */
void printVdcCol(screen *scr, uchar x, uchar y, uchar color, char *str) {
	ushort len = strlen(str);
	/* No need to print empty string */
	if (len > 0) {
		fillVdcMem((uchar*) (y * scr->scrWidth) + (ushort) scr->scrColMem + x,
				len, scr->color[color]);
		printVdc(scr, x, y, str);
	}
}
