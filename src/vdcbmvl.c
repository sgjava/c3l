/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include <graphics.h>
#include <screen.h>
#include "hitech.h"

/*
 * Optimized vertical line algorithm uses less calculation than setVdcPix.
 */
void drawVdcLineV(ushort x, ushort y, ushort len, uchar setPix) {
	static uchar vdcBitTable[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    ushort vdcMem = (ushort) bmpMem;
    ushort pixByte = vdcMem + (y << 6) + (y << 4) + (x >> 3);
    uchar vBit = vdcBitTable[x & 0x07];
    uchar saveByte, i;
    /* Plot pixels */
    for (i = 0; i < len; i++) {
        outVdc(vdcUpdAddrHi, (uchar) (pixByte >> 8));
        outVdc(vdcUpdAddrLo, (uchar) pixByte);
        saveByte = inVdc(vdcCPUData);
        outVdc(vdcUpdAddrHi, (uchar) (pixByte >> 8));
        outVdc(vdcUpdAddrLo, (uchar) pixByte);
        if (setPix) {
            outVdc(vdcCPUData, saveByte | vBit);
        } else {
            outVdc(vdcCPUData, saveByte & ~vBit);
        }
        pixByte += scrWidth;
    }
}
