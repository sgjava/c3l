/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <vdc.h>
#include <graphics.h>

/*
 * Set pixel.
 */
void setVdcPix(ushort x, ushort y) {
	static uchar vdcBitTable[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    ushort vdcMem = (ushort) bmpMem;
    uchar saveByte;
    ushort pixByte;
    pixByte = vdcMem + (y << 6) + (y << 4) + (x >> 3);
    outVdc(vdcUpdAddrHi, (uchar) (pixByte >> 8));
    outVdc(vdcUpdAddrLo, (uchar) pixByte);
    saveByte = inVdc(vdcCPUData);
    outVdc(vdcUpdAddrHi, (uchar) (pixByte >> 8));
    outVdc(vdcUpdAddrLo, (uchar) pixByte);
    outVdc(vdcCPUData, saveByte | vdcBitTable[x & 0x07]);
}
