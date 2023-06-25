/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>

/*
 * Copy VDC memory to C string.
 */
void copyVicToStr(screen *scr, ushort offset, char *str, ushort len) {
	ushort i;
	for (i = 0; i < len; i++) {
		str[i] = scr->scrMem[i + offset];
	}
	/* C style string */
	str[len] = 0x00;
}
