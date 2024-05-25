/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <string.h>
#include <vic.h>

/*
 * Print with color.
 */
void printVicCol(const screen *scr, const unsigned char x, const unsigned char y, const unsigned char color, const char *str) {
	unsigned int colOfs = (unsigned int) scr->scrColMem + (y * scr->scrWidth) + x;
	unsigned int len = strlen(str);
	/* 0 length not allowed for fillVicMemCol */
	if (len > 0) {
		fillVicMemCol(colOfs, len, scr->color[color]);
		printVic(scr, x, y, str);
	}
}
