/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>

/*
 * Fill memory with uchar value.
 */
void fillVicMem(uchar *mem, ushort len, uchar value) {
	register ushort i;
	for (i = 0; i < len; i++) {
		mem[i] = value;
	}
}
