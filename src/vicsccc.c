/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <screen.h>
#include <vic.h>

/*
 * Clear color memory. Color memory is port mapped.
 */
void clearVicCol(uchar c) {
	register ushort i;
	for (i = 0; i < scrSize; i++) {
		outp((ushort) scrColMem + i, c);
	}
}