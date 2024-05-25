/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Set foreground and background color.
 */
void setVdcFgBg(const unsigned char f, const unsigned char b) {
	outVdc(vdcFgBgColor, (f << 4) | (b & 0x0f));
}
