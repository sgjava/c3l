/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

void setVicBmpMem(unsigned char bmpLoc) {
	outp(vicMemCtrl, (inp(vicMemCtrl) & 0xf0) | (bmpLoc << 3));
}
