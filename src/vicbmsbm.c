/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vic.h"
#include "hitech.h"

/*
 * Set bitmap mode.
 */
void setVicBmpMode(uchar mmuRcr, uchar vicBank, uchar scrLoc, uchar bmpLoc) {
	setVicMmuBank(mmuRcr);
	setVicBank(vicBank);
	setVicMode(0, 1, 0);
	setVicScrMem(scrLoc);
	setVicBmpMem(bmpLoc);
}
