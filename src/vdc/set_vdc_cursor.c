/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Set cursor's top and bottom scan lines and mode.
 */
void setVdcCursor(const unsigned char top, const unsigned char bottom, const unsigned char mode) {
	outVdc(vdcCurStScanLine, (top | (mode << 5)));
	outVdc(vdcCurEndScanLine, bottom);
}
