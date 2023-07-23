/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <stdlib.h>

/*
 * Allocate memory in TPA for VIC to use. maxBank Should be 0 - 2. Bank 3
 * should be allocated manually since that's the top bank of memory and
 * not all 16K is available.
 */
uchar* allocVicMem(uchar maxBank) {
	uchar bank, *vicMem;
	ushort gap;
	vicMem = (uchar*) malloc(1);
	bank = (ushort) vicMem / 16384;
	gap = 16384 - ((ushort) vicMem - (bank * 16384));
	realloc(vicMem, ((maxBank - bank) * 16384) + gap);
	return vicMem;
}
