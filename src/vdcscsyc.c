/*
 * C128 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"

/*
 * Scroll line color up given y1 and y2 lines in current page.
 * copyVdcMem the entire block for speed.
 */
void scrollVdcUpYCol(screen *scr, uchar y1, uchar y2) {
	ushort colOfs = (y1 * scr->scrWidth) + (ushort) scr->scrColMem;
	scrollVdcUpY(scr, y1, y2);
	copyVdcMem(colOfs, colOfs - scr->scrWidth, (y2 - y1 + 1) * scr->scrWidth);
}
