/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <graphics.h>
#include <vic.h>
#include "hitech.h"

/*
 * Clear screen using 16 bit word.
 */
void clearVicBmp(uchar c) {
    fillVicMem(bmpMem, bmpSize >> 1, (c << 8) + c);
}
