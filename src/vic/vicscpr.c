/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <string.h>

/*
 * Print without color.
 */
void printVic(screen *scr, uchar x, uchar y, char *str) {
	ushort scrOfs = (y * scr->scrWidth) + x;
	ushort len = strlen(str);
	ushort i;
	for (i = 0; i < len; i++) {
		scr->scrMem[scrOfs + i] = str[i];
	}
}
