/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include "hitech.h"
#include "sys.h"

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void doneVic(screen *scr, uchar bgCol, uchar fgCol) {
	/* Restore screen/border colors */
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* Clear color to black */
	(scr->clearScrCol)(scr, vicBlack);
	/* CPM default */
	setVicChrMode(0, 0, 11, 3);
}
