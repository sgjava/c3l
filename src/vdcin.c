/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <vdc.h>

/*
 * Read VDC register.
 */
uchar inVdc(uchar regNum) {
	outp(vdcStatusReg, regNum);
	while ((inp(vdcStatusReg) & 0x80) == 0x00)
		;
	return (inp(vdcDataReg));
}
