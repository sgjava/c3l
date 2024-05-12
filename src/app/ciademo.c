/*
 * C128 CP/M C Library C3L
 *
 * CIA 2 timer A and B millisecond demo. CIA 1 TOD used to calibrate.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 *
 */

#pragma output noprotectmsdos

#include <cia.h>
#include <stdio.h>
#include <stdlib.h>

main() {
	unsigned long i, startCia, endCia;
	unsigned int timerVal;
	unsigned char tens;
	if (inp(cia1 + ciaCtrlRegA) & 0x80) {
		printf("\nCIA 1 50 Hz\n");
	} else {
		printf("\nCIA 1 60 Hz\n");
	}
	printf("Empty loop elapsed time test.\n");
	initCia();
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	startTimerAB(cia2, ciaMs, 0xffff, ciaCountA);
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
	printf("Milliseconds CIA timer %u, CIA TOD %lu\n", timerVal,
			(endCia - startCia));
	doneCia();
}
