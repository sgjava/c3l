/*
 * C128 CP/M C Library C3L
 *
 * CIA 2 timer A and B millisecond demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <stdio.h>
#include <sys.h>
#include "cia.h"
#include "app.h"

main() {
	ushort timerVal;
	initCia();
	/* Timer A counts milliseconds up to 65535 times or ~65 seconds */
	initCiaTimer(ciaMs, 0xffff);
	printf("Start timer\n");
	outp(cia2CtrlRegA, ciaCpuCont);
	printf("Stop timer\n");
	outp(cia2CtrlRegA, ciaStopTimer);
	timerVal = 0xffff - (inp(cia2TimerBHi) * 256 + inp(cia2TimerBLo));
	printf("Milliseconds elapsed: %u\n", timerVal);
	doneCia();
}
