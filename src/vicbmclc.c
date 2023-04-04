/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <graphics.h>
#include "hitech.h"

/*
 * Clear bitmap color memory.
 */
void clearVicBmpCol(uchar c) {
    fillVicMem(bmpColMem, bmpColSize >> 1, (c << 8) + c);
}
