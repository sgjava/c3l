/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vic.h"
#include "hitech.h"
#include <sys.h>

/*
 * Set character set 0-7 memory location (2K per character set).
 */
void setVicChrMem(uchar chrLoc) {
	outp(vicMemCtrl, (inp(vicMemCtrl) & 0xf0) | (chrLoc << 1));
}
