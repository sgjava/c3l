/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"

/*
 * Set cursor's top and bottom scan lines and mode.
 */
void setVdcCursor(uchar top, uchar bottom, uchar mode) {
	outVdc(vdcCurStScanLine, (top | (mode << 5)));
	outVdc(vdcCurEndScanLine, bottom);
}
