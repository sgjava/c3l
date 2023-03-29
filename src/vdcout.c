/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <vdc.h>

/*
 * Write VDC register.
 */
void outVdc(uchar regNum, uchar regVal) {
	outp(vdcStatusReg, regNum);
	while ((inp(vdcStatusReg) & 0x80) == 0x00)
		;
	outp(vdcDataReg, regVal);
}
