/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

/*
 * Allocate memory in TPA for VIC to use. maxBank Should be 0 - 2. Bank 3
 * should be allocated manually since that's the top bank of memory and
 * not all 16K is available.
 */
unsigned char* allocVicMem(unsigned char maxBank) {
	unsigned char bank, *vicMem;
	unsigned int gap;
	vicMem = (unsigned char*) malloc(1);
	bank = (unsigned int) vicMem / 16384;
	gap = 16384 - ((unsigned int) vicMem - (bank * 16384));
	realloc(vicMem, ((maxBank - bank) * 16384) + gap);
	return vicMem;
}
