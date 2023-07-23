/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Turn attributes on.
 */
void setVdcAttrsOn() {
	outVdc(vdcHzSmScroll, inVdc(vdcHzSmScroll) | 0x40);
}
