/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <sys.h>
#include <vic.h>

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void doneVic(uchar bgCol, uchar fgCol) {
	/* Restore screen/border colors */
	outp(vicBorderCol, bgCol);
	outp(vicBgCol0, fgCol);
	/* CPM default */
	setVicChrMode(0, 0, 11, 3);
}
