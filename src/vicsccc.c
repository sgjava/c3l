/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "vic.h"
#include "hitech.h"
#include <sys.h>

/*
 * Clear color memory. Color memory is port mapped.
 */
void clearVicCol(screen *scr, uchar c) {
	register ushort i;
	for (i = 0; i < scr->scrSize; i++) {
		outp((ushort) scr->scrColMem + i, c);
	}
}
