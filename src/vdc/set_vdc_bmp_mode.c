/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Set bitmap memory location, attribute memory location and bitmap mode.
 */
void setVdcBmpMode(unsigned int dispPage, unsigned int attrPage) {
	setVdcDspPage(dispPage, attrPage);
	outVdc(vdcHzSmScroll, inVdc(vdcHzSmScroll) | 0x80);
}
