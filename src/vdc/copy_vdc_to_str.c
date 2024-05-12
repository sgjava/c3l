/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Copy VDC memory to C string.
 */
void copyVdcToStr(screen *scr, unsigned int offest, char *str, unsigned int len) {
	unsigned int vdcOfs = (unsigned int) scr->scrMem + offest, i;
	outVdc(vdcUpdAddrHi, (char) (vdcOfs >> 8));
	outVdc(vdcUpdAddrLo, (char) vdcOfs);
	for (i = 0; i < len; i++) {
		str[i] = inVdc(vdcCPUData);
	}
	/* C style string */
	str[len] = 0x00;
}
