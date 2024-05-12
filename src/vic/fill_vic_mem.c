/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>

/*
 * Fill memory with unsigned char value.
 */
void fillVicMem(unsigned char *mem, unsigned int len, unsigned char value) {
	unsigned int i;
	for (i = 0; i < len; i++) {
		mem[i] = value;
	}
}
