/*
 * C128 CP/M C Library C3L
 *
 * CIA 2 timer A and B millisecond demo. CIA 1 TOD used to calibrate.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <stdio.h>
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

main() {
	ulong i, startCia, endCia;
	ushort timerVal;
	uchar tens;
	if (inp(cia1 + ciaCtrlRegA) & 0x80) {
		printf("\nCIA 1 50 Hz\n");
	} else {
		printf("\nCIA 1 60 Hz\n");
	}
	printf("Empty loop elapsed time test.\n");
	initCia();
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff);
	tens = inp(cia1 + ciaTodTen);
	/* Wait for tenth of a second to change */
	while (inp(cia1 + ciaTodTen) == tens)
		;
	startCia = todToMs(cia1);
	outp(cia2 + ciaCtrlRegA, ciaCpuCont);
	for (i = 0; i < 130000; ++i) {
	}
	/* Stop timer A/B */
	outp(cia2 + ciaCtrlRegA, ciaStopTimer);
	endCia = todToMs(cia1);
	timerVal = 0xffff
			- (inp(cia2 + ciaTimerBHi) * 256 + inp(cia2 + ciaTimerBLo));
	printf("Milliseconds CIA timer %u, CIA TOD %u\n", timerVal,
			endCia - startCia);
	doneCia();
}
