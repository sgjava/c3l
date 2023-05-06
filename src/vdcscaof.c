/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vdc.h"
#include "hitech.h"

/*
 * Turn attributes off.
 */
void setVdcAttrsOff() {
	outVdc(vdcHzSmScroll, inVdc(vdcHzSmScroll) & 0xbf);
}
