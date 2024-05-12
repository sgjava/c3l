/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>

/*
 * Clear screen using 16 bit word.
 */
void clearVicScr(screen *scr, unsigned char c) {
	fillVicMem(scr->scrMem, scr->scrSize, c);
}
