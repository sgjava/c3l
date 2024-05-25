/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vdc.h>

/*
 * Clear screen.
 */
void clearVdcScr(const screen *scr, const unsigned char c) {
	fillVdcMem(scr->scrMem, scr->scrSize, c);
}
