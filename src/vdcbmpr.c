/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <string.h>
#include <hitech.h>
#include <vdc.h>
#include <graphics.h>

/*
 * Print without color. Optimized by setting VDC address once for each scan line.
 */
void printVdcBmp(uchar x, uchar y, char *str) {
    ushort vdcMem = (ushort) bmpMem;
    ushort dispOfs = ((y * 80) * 8) + vdcMem + x;
    ushort len = strlen(str);
    ushort i, chrOfs;
    uchar c;
    /* Draw 8 scan lines */
    for (c = 0; c < 8; c++) {
        outVdc(vdcUpdAddrHi, (uchar) (dispOfs >> 8));
        outVdc(vdcUpdAddrLo, (uchar) dispOfs);
        for (i = 0; i < len; i++) {
            chrOfs = (str[i] << 3) + c;
            outVdc(vdcCPUData, bmpChrMem[chrOfs]);
        }
        /* Next scan line */
        dispOfs += 80;
    }
}
