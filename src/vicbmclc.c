/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include "hitech.h"

/*
 * Clear bitmap color memory.
 */
void clearVicBmpCol(screen *scr, uchar c) {
	fillVicMem(scr->bmpColMem, scr->bmpColSize, c);
}
