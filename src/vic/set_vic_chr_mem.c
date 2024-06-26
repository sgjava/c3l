/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

/*
 * Set character set 0-7 memory location (2K per character set).
 */
void setVicChrMem(const unsigned char chrLoc) {
	outp(vicMemCtrl, (inp(vicMemCtrl) & 0xf0) | (chrLoc << 1));
}
