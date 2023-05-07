/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <string.h>
#include <vic.h>

/*
 * Print with color.
 */
void printVicCol(screen *scr, uchar x, uchar y, uchar color, char *str) {
	ushort colOfs = (ushort) scr->scrColMem + (y * scr->scrWidth) + x;
	ushort len = strlen(str);
	fillVicMemCol(colOfs, len, color);
	printVic(scr, x, y, str);
}
