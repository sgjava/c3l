/*
 * C128 6526 CIA functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 * Set CIA count down timers. Timer B counts timer A.
 */
void startTimerAB(ushort cia, ushort timerA, ushort timerB, uchar latch) {
	/* CIA Timer A lo */
	outp(cia + ciaTimerALo, (uchar) timerA);
	/* CIA Timer A hi */
	outp(cia + ciaTimerAHi, (uchar) (timerA >> 8));
	/* CIA Timer B lo */
	outp(cia + ciaTimerBLo, (uchar) timerB);
	/* CIA Timer B hi */
	outp(cia + ciaTimerBHi, (uchar) (timerB >> 8));
	/* Link time to count and enable timer */
	outp(cia + ciaCtrlRegB, latch);
}
