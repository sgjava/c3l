/*
 * C128 6526 CIA functions.
 *
 * Keys are mapped the same as getch for the most part.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>

/*
 * Get left shift key column. If column not found then 8 is returned.
 */
uchar getLsKeyCol(uchar keyVal) {
	static uchar lsKeyCol[8] =
			{ 0x7e, 0x7d, 0x7b, 0x77, 0x6f, 0x5f, 0x3f, 0x7f };
	register uchar i = 0;
	while ((i < 8) && (lsKeyCol[i] != keyVal)) {
		i++;
	}
	return i;
}
