/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>

/*
 * Clear color memory. Color memory is port mapped.
 */
void clearVicCol(const screen *scr, const unsigned char c) {
	fillVicMemCol((unsigned int) scr->scrColMem, scr->scrSize, scr->color[c]);
}
