/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <vdc.h>

/*
 * Or VDC byte with value and store it.
 */
void orVdcByte(ushort vdcMem, uchar value) {
	uchar saveByte;
	outVdc(vdcUpdAddrHi, (uchar) (vdcMem >> 8));
	outVdc(vdcUpdAddrLo, (uchar) vdcMem);
	saveByte = inVdc(vdcCPUData);
	outVdc(vdcUpdAddrHi, (uchar) (vdcMem >> 8));
	outVdc(vdcUpdAddrLo, (uchar) vdcMem);
	outVdc(vdcCPUData, saveByte | value);
}
