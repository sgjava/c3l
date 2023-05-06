/*
 * C128 6526 CIA functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 * Set CIA2 count down timers. Timer B counts timer A.
 */
void initCiaTimer(ushort timerA, ushort timerB) {
	/* CIA 2 Timer A lo */
	outp(cia2TimerALo, (uchar) timerA);
	/* CIA 2 Timer A hi */
	outp(cia2TimerAHi, (uchar) (timerA >> 8));
	/* CIA 2 Timer B lo */
	outp(cia2TimerBLo, (uchar) timerB);
	/* CIA 2 Timer B hi */
	outp(cia2TimerBHi, (uchar) (timerB >> 8));
	/* Link time to count and enable timer */
	outp(cia2CtrlRegB, ciaCountA);
}
