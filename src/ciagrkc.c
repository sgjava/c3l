/*
 * C128 6526 CIA functions.
 *
 * Keys are mapped the same as getch for the most part.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include "cia.h"
#include "hitech.h"

/*
 * Get right shift key column. If column not found then 8 is returned.
 */
uchar getRsKeyCol(uchar keyVal) {
	static uchar rsKeyCol[8] = { 0xee, 0xed, 0xeb, 0xe7, 0xdf, 0xcf, 0xaf, 0x6f };
	register uchar i = 0;
	while ((i < 8) && (rsKeyCol[i] != keyVal)) {
		i++;
	}
	return i;
}
