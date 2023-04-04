/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>
#include "hitech.h"

/*
 * Clear screen using 16 bit word.
 */
void clearVicScr(uchar c) {
	fillVicMem(scrMem, scrSize >> 1, (c << 8) + c);
}
