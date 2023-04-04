/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <string.h>
#include <screen.h>
#include <vdc.h>
#include "hitech.h"

/*
 * Print without color.
 */
void printVdc(uchar x, uchar y, char *str) {
	ushort dispOfs = (y * scrWidth) + (ushort) scrMem + x;
	ushort len = strlen(str);
	ushort i;
	outVdc(vdcUpdAddrHi, (uchar) (dispOfs >> 8));
	outVdc(vdcUpdAddrLo, (uchar) dispOfs);
	for (i = 0; i < len; i++) {
		outVdc(vdcCPUData, str[i]);
	}
}
