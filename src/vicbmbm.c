/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <vic.h>

void setVicBmpMem(uchar bmpLoc) {
    outp(vicMemCtrl, (inp(vicMemCtrl) & 0xf0) | (bmpLoc << 3));
}
