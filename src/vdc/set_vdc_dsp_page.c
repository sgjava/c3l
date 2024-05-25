/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Sets which display and attribute page is showing.
 */
void setVdcDspPage(const unsigned int dispPage, const unsigned int attrPage) {
	outVdc(vdcDspStAddrHi, (unsigned char) (dispPage >> 8));
	outVdc(vdcDspStAddrLo, (unsigned char) dispPage);
	outVdc(vdcAttrStAddrHi, (unsigned char) (attrPage >> 8));
	outVdc(vdcAttrStAddrLo, (unsigned char) attrPage);
}
