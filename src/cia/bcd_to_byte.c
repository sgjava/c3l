/*
 * C128 6526 CIA demo functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>

/*
 * Convert BCD byte to base 10 byte.
 */
unsigned char bcdToByte(unsigned char bcd) {
	return ((bcd >> 4) * 10) + (bcd & 0x0f);
}
