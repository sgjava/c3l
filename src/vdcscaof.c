/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <vdc.h>

/*
 * Turn attributes off.
 */
void setVdcAttrsOff() {
	outVdc(vdcHzSmScroll, inVdc(vdcHzSmScroll) & 0xbf);
}
