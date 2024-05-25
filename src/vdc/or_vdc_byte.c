/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Or VDC byte with value and store it.
 */
void orVdcByte(const unsigned int vdcMem, const unsigned char value) {
	unsigned char saveByte;
	outVdc(vdcUpdAddrHi, (unsigned char) (vdcMem >> 8));
	outVdc(vdcUpdAddrLo, (unsigned char) vdcMem);
	saveByte = inVdc(vdcCPUData);
	outVdc(vdcUpdAddrHi, (unsigned char) (vdcMem >> 8));
	outVdc(vdcUpdAddrLo, (unsigned char) vdcMem);
	outVdc(vdcCPUData, saveByte | value);
}
