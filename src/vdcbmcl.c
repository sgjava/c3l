/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"

/*
 * Clear screen.
 */
void clearVdcBmp(screen *scr, uchar c) {
	fillVdcMem(scr->bmpMem, scr->bmpSize, c);
}
