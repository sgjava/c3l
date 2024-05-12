/*
 * C128 6526 CIA functions.
 *
 * Keys are mapped the same as getch for the most part.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>

/*
 * Get key column. If column not found then 8 is returned.
 */
unsigned char getKeyCol(unsigned char keyVal) {
	static unsigned char keyCol[8] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf,
			0x7f };
	unsigned char i = 0;
	while ((i < 8) && (keyCol[i] != keyVal)) {
		i++;
	}
	return i;
}
