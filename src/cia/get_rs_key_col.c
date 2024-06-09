/*
 * C128 6526 CIA functions.
 *
 * Keys are mapped the same as getch for the most part.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>

/*
 * Get right shift key column. If column not found then 8 is returned.
 */
unsigned char getRsKeyCol(const unsigned char keyVal) {
	static unsigned char rsKeyCol[8] = { 0xee, 0xed, 0xeb, 0xe7, 0xdf, 0xcf, 0xaf, 0x6f };
	unsigned char i = 0;
	while ((i < 8) && (rsKeyCol[i] != keyVal)) {
		i++;
	}
	return i;
}
