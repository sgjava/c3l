/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vdc.h"
#include "hitech.h"

/*
 * Set foreground and background color.
 */
void setVdcFgBg(uchar f, uchar b) {
	outVdc(vdcFgBgColor, (f << 4) | b);
}
