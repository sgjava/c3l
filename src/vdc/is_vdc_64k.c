/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Is VDC in 64k mode?
 */
unsigned char isVdc64k() {
	if (inVdc(vdcChSetStAddr) & 0x10 == 0x10) {
		return 1;
	} else {
		return 0;
	}
}
