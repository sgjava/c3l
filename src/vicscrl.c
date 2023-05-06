/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <screen.h>
#include <stdlib.h>
#include <sys.h>
#include <vic.h>

/*
 * Use screen memory as simple input line. Only backspace supported, but insert
 * and delete could be added later.
 */
char* readVicLine(screen *scr, uchar x, uchar y, uchar len) {
	uchar strLen;
	char *str;
	uchar keyVal, lastKeyVal, i;
	ushort scrOfs = (y * scr->scrWidth) + x;
	ushort scrMin = scrOfs;
	ushort scrMax = scrMin + len - 1;
	lastKeyVal = 0x00;
	/* Show cursor */
	scr->scrMem[scrOfs] = '_';
	do {
		keyVal = decodeKey();
		/* Debounce if current key equals last key */
		if (keyVal == lastKeyVal) {
			i = 0;
			do {
				/* ~1/60th second delay */
				while (inp(vicRaster) != 0x00)
					;
				keyVal = decodeKey();
				i++;
			} while ((keyVal == lastKeyVal) && (i < 8));
		}
		lastKeyVal = keyVal;
		/* Decoded key? */
		if (keyVal != 0x00) {
			/* Backspace? */
			if (keyVal == 0x7f) {
				if (scrOfs > scrMin) {
					scr->scrMem[scrOfs] = ' ';
					scrOfs--;
				}
			} else {
				if ((scrOfs <= scrMax) && (keyVal != 0x0d)) {
					scr->scrMem[scrOfs] = keyVal;
					scrOfs++;
				}
			}
			/* Show cursor */
			scr->scrMem[scrOfs] = '_';
		}
	} while (keyVal != 0x0d);
	/* Figure out string length based on current screen offset */
	strLen = scrOfs - scrMin;
	str = (char*) malloc(strLen + 1);
	/* Screen to string */
	for (i = 0; i < strLen; i++) {
		str[i] = scr->scrMem[scrMin + i];
	}
	str[strLen] = 0;
	return str;
}
