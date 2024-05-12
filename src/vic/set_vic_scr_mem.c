/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

/*
 * Set screen 0-15 memory location (1K per screen).
 */
void setVicScrMem(unsigned char scrLoc) {
	outp(vicMemCtrl, (inp(vicMemCtrl) & 0x0f) | (scrLoc << 4));
}
