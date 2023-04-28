/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"

/*
 * Clear screen.
 */
void clearVdcScr(screen *scr, uchar c) {
	fillVdcMem(scr->scrMem, scr->scrSize, c);
}
