/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"
#include "sys.h"

/*
 * Write VDC register.
 */
void outVdc(uchar regNum, uchar regVal) {
	outp(vdcStatusReg, regNum);
	while ((inp(vdcStatusReg) & 0x80) == 0x00)
		;
	outp(vdcDataReg, regVal);
}
