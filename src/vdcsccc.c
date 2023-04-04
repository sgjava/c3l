/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>
#include "hitech.h"

/*
 * Clear screen color.
 */
void clearVdcScrCol(uchar c) {
	fillVdcMem((ushort) scrColMem, scrSize, c);
}
