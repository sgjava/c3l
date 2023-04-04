/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>
#include "hitech.h"

/*
 * Clear screen.
 */
void clearVdcScr(uchar c) {
	fillVdcMem((ushort) scrMem, scrSize, c);
}
