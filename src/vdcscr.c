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
void clearVdcScrCol(uchar c) {
	fillVdcMem((ushort) scrColMem, scrSize, c);
}

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

/*
 * Print with color.
 */
void printVdcCol(uchar x, uchar y, uchar color, char *str) {
	fillVdcMem((y * scrWidth) + (ushort) scrColMem + x, strlen(str), color);
	printVdc(x, y, str);
}

/*
 * Scroll line up given y1 and y2 lines in current page.
 * copyVdcMem the entire block for speed.
 */
void scrollVdcUpY(uchar y1, uchar y2) {
	ushort dispOfs = (y1 * 80) + (ushort) scrMem;
	copyVdcMem(dispOfs, dispOfs - scrWidth, (y2 - y1 + 1) * scrWidth);
}

/*
 * Scroll line color up given y1 and y2 lines in current page.
 * copyVdcMem the entire block for speed.
 */
void scrollVdcUpYCol(uchar y1, uchar y2) {
	ushort colOfs = (y1 * 80) + (ushort) scrColMem;
	scrollVdcUpY(y1, y2);
	copyVdcMem(colOfs, colOfs - scrWidth, (y2 - y1 + 1) * scrWidth);
}

/*
 * Scroll line up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVdcUp(uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized  */
	if (x2 - x1 + 1 == scrWidth) {
		scrollVdcUpY(y1, y2);
	} else {
		uchar len = x2 - x1 + 1;
		ushort dispOfs = (y1 * 80) + (ushort) scrMem + x1;
		for (; y1 <= y2; y1++) {
			copyVdcMem(dispOfs, dispOfs - scrWidth, len);
			dispOfs += scrWidth;
		}
	}
}

/*
 * Scroll color window up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVdcUpCol(uchar x1, uchar y1, uchar x2, uchar y2) {
	/* If line is screen width use optimized  */
	if (x2 - x1 + 1 == scrWidth) {
		scrollVdcUpYCol(y1, y2);
	} else {
		uchar len = x2 - x1 + 1;
		ushort colOfs = (y1 * scrWidth) + (ushort) scrColMem + x1;
		scrollVdcUp(x1, y1, x2, y2);
		for (; y1 <= y2; y1++) {
			copyVdcMem(colOfs, colOfs - scrWidth, len);
			colOfs += scrWidth;
		}
	}
}
