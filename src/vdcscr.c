/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <string.h>
#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Sets which disp and attr page is showing.
 */
void setVdcDspPage(ushort dispPage, ushort attrPage) {
    outVdc(vdcDspStAddrHi, (uchar) (dispPage >> 8));
    outVdc(vdcDspStAddrLo, (uchar) dispPage);
    outVdc(vdcAttrStAddrHi, (uchar) (attrPage >> 8));
    outVdc(vdcAttrStAddrLo, (uchar) attrPage);
}

/*
 * Set foreground and background color.
 */
void setVdcFgBg(uchar f, uchar b) {
    outVdc(vdcFgBgColor, (f << 4) | b);
}

/*
 * Turn attributes on.
 */
void setVdcAttrsOn() {
    outVdc(vdcHzSmScroll, inVdc(vdcHzSmScroll) | 0x40);
}

/*
 * Turn attributes off.
 */
void setVdcAttrsOff() {
    outVdc(vdcHzSmScroll, inVdc(vdcHzSmScroll) & 0xbf);
}

/*
 * Set cursor's top and bottom scan lines and mode.
 */
void setVdcCursor(uchar top, uchar bottom, uchar mode) {
    outVdc(vdcCurStScanLine, (top | (mode << 5)));
    outVdc(vdcCurEndScanLine, bottom);
}

/*
 * Clear screen.
 */
void clearVdcScr(uchar c) {
    fillVdcMem((ushort) scrMem, scrSize, c);
}

/*
 * Clear screen color.
 */
void clearVdcCol(uchar c) {
    fillVdcMem((ushort) scrColMem, scrSize, c);
}

/*
 * Print without color.
 */
void printVdc(uchar x, uchar y, char *str) {
    ushort dispOfs = (y * 80) + (ushort) scrMem + x;
    ushort len = strlen(str);
    ushort i;
    outVdc(vdcUpdAddrHi, (uchar) (dispOfs >> 8));
    outVdc(vdcUpdAddrLo, (uchar) dispOfs);
    for (i = 0; i < len; i++) {
        outVdc(vdcCPUData, str[i]);
    }
}

/*
 * Print with color.
 */
void printVdcCol(uchar x, uchar y, uchar color, char *str) {
    fillVdcMem((y * 80) + (ushort) scrColMem + x, strlen(str), color);
    printVdc(x, y, str);
}
