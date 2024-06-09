/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <string.h>
#include <vdc.h>

/*
 * Print with color.
 */
void printVdcCol(const screen *scr, const unsigned char x, const unsigned char y, const unsigned char color, const char *str) {
	unsigned int len = strlen(str);
	/* No need to print empty string */
	if (len > 0) {
		fillVdcMem((unsigned char*) (y * scr->scrWidth) + (unsigned int) scr->scrColMem + x, len, scr->color[color]);
		printVdc(scr, x, y, str);
	}
}
