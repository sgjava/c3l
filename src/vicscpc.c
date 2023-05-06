/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <string.h>
#include "vic.h"
#include "hitech.h"

/*
 * Print with color.
 */
void printVicCol(screen *scr, uchar x, uchar y, uchar color, char *str) {
	ushort colOfs = (ushort) scr->scrColMem + (y * scr->scrWidth) + x;
	ushort len = strlen(str);
	ushort i;
	for (i = 0; i < len; i++) {
		outp(colOfs + i, color);
	}
	printVic(scr, x, y, str);
}
