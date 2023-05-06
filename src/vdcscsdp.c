/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <vdc.h>

/*
 * Sets which display and attribute page is showing.
 */
void setVdcDspPage(ushort dispPage, ushort attrPage) {
	outVdc(vdcDspStAddrHi, (uchar) (dispPage >> 8));
	outVdc(vdcDspStAddrLo, (uchar) dispPage);
	outVdc(vdcAttrStAddrHi, (uchar) (attrPage >> 8));
	outVdc(vdcAttrStAddrLo, (uchar) attrPage);
}
