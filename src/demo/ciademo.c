/*
 * C128 CP/M C Library C3L
 *
 * DS12C887 - Real Time Clock demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <stdio.h>
#include <sys.h>
#include "cia.h"

main() {
	/* ~1 millisecond */
	int timerA = 992;
	int timerB = 0xffff;
	int timerVal;
	/* Clear all CIA 1 IRQ enable bits */
	outp(cia1Icr, ciaClearIcr);
	/* Clear CIA 1 ICR status */
	inp(cia1Icr);
	/* Clear all CIA 2 IRQ enable bits */
	outp(cia2Icr, ciaClearIcr);
	/* Clear CIA 2 ICR status */
	inp(cia2Icr);
	/* CIA 2 Timer A lo */
	outp(cia2TimerALo, (uchar) timerA);
	/* Timer A hi */
	outp(cia2TimerAHi, (uchar) (timerA >> 8));
	/* CIA 2 Timer B lo */
	outp(cia2TimerBLo, (uchar) timerB);
	/* CIA 2 Timer B hi */
	outp(cia2TimerBHi, (uchar) (timerB >> 8));
	/* Link time to count and enable timer */
	outp(cia2CtrlRegB, ciaCountA);
	printf("Start timer\n");
	outp(cia2CtrlRegA, ciaCpuCont);
	printf("Stop timer\n");
	outp(cia2CtrlRegA, ciaStopTimer);
	timerVal = timerB - (inp(cia2TimerBHi) * 256 + inp(cia2TimerBLo));
	printf("Milliseconds elapsed: %u\n", timerVal);
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, ciaEnableIrq);
}
