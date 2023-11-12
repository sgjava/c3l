/*
 * C128 6526 CIA demo functions..
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 * Convert bcd byte to base 10 byte.
 */
uchar bcdToByte(uchar bcd) {
	return ((bcd >> 4) * 10) + (bcd & 0x0f);
}

/*
 Convert TOD clock to milliseconds since midnight.
 */
ulong todToMs(ushort cia) {
	/* Reading hours first stops updating registers */
	uchar hour = inp(cia + ciaTodHrs);
	/* Bit 7 of hour is used as a flag for AM/PM (1 = PM, 0 = AM) */
	if (hour & 0x80) {
		hour = bcdToByte(hour) + 12;
	}
	return (hour * 3600000) + (bcdToByte(inp(cia + ciaTodMin)) * 60000)
			+ (bcdToByte(inp(cia + ciaTodSec)) * 1000)
			+ (bcdToByte(inp(cia + ciaTodTen)) * 100);
}
