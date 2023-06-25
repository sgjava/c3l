/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Copy VDC memory to C string.
 */
void copyVdcToStr(screen* scr, ushort offest, char *str, ushort len) {
	ushort vdcOfs = (ushort) scr->scrMem + offest, i;
	outVdc(vdcUpdAddrHi, (char) (vdcOfs >> 8));
	outVdc(vdcUpdAddrLo, (char) vdcOfs);
	for (i = 0; i < len; i++) {
		str[i] = inVdc(vdcCPUData);
	}
	/* C style string */
	str[len] = 0x00;
}
