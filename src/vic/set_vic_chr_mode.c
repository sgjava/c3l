/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>

/*
 * Set standard character mode (no MCM or ECM).
 */
void setVicChrMode(const unsigned char mmuRcr, const unsigned char vicBank, const unsigned char scrLoc, const unsigned char chrLoc) {
	setVicMmuBank(mmuRcr);
	setVicBank(vicBank);
	setVicMode(0, 0, 0);
	setVicScrMem(scrLoc);
	setVicChrMem(chrLoc);
}
