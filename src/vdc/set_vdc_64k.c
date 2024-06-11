/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Set VDC to 64k mode
 */
void setVdc64k() {
	outVdc(vdcChSetStAddr, inVdc(vdcChSetStAddr) | 0x10);
}
