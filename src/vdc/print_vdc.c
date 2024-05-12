/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <string.h>
#include <vdc.h>

/*
 * Print without color.
 */
void printVdc(screen *scr, unsigned char x, unsigned char y, char *str) {
	unsigned int dispOfs = (y * scr->scrWidth) + (unsigned int) scr->scrMem + x;
	unsigned int len = strlen(str);
	unsigned int i;
	outVdc(vdcUpdAddrHi, (unsigned char) (dispOfs >> 8));
	outVdc(vdcUpdAddrLo, (unsigned char) dispOfs);
	for (i = 0; i < len; i++) {
		outVdc(vdcCPUData, str[i]);
	}
}
