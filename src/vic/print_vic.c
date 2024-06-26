/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <screen.h>
#include <string.h>

/*
 * Print without color.
 */
void printVic(const screen *scr, const unsigned char x, const unsigned char y, const char *str) {
	unsigned int scrOfs = (y * scr->scrWidth) + x;
	unsigned int len = strlen(str);
	unsigned int i;
	for (i = 0; i < len; i++) {
		scr->scrMem[scrOfs + i] = str[i];
	}
}
