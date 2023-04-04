/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <cia.h>
#include <screen.h>
#include <vic.h>
#include "hitech.h"
#include "sys.h"

/*
 * Use screen memory as simple input line. Only backspace supported, but insert
 * and delete could be added later.
 */
char* readVicLine(uchar x, uchar y, uchar len) {
	uchar strLen;
	char *str;
	uchar keyVal, lastKeyVal, i;
	ushort scrOfs = (y * scrWidth) + x;
	ushort scrMin = scrOfs;
	ushort scrMax = scrMin + len - 1;
	lastKeyVal = 0x00;
	/* Show cursor */
	scrMem[scrOfs] = '_';
	do {
		keyVal = decodeKey();
		/* Debounce if current key equals last key */
		if (keyVal == lastKeyVal) {
			i = 0;
			do {
				/* ~1/60th second delay */
				while (inp(vicRaster) != 0xff)
					;
				while (inp(vicRaster) == 0xff)
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
					scrMem[scrOfs] = ' ';
					scrOfs--;
				}
			} else {
				if ((scrOfs <= scrMax) && (keyVal != 0x0d)) {
					scrMem[scrOfs] = keyVal;
					scrOfs++;
				}
			}
			/* Show cursor */
			scrMem[scrOfs] = '_';
		}
	} while (keyVal != 0x0d);
	/* Figure out string length based on current screen offset */
	strLen = scrOfs - scrMin;
	str = (char*) malloc(strLen + 1);
	/* Screen to string */
	for (i = 0; i < strLen; i++) {
		str[i] = scrMem[scrMin + i];
	}
	str[strLen] = 0;
	return str;
}
