/*
 * C128 6526 CIA functions.
 *
 * Start CIA timer A.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 Start CIA timer A using Hz value and latch for mode.
 */
void startTimerA(ushort cia, ushort hz, uchar latch) {
	ushort timerA = ciaTimerFreq / hz;
	/* CIA Timer A lo */
	outp(cia+ciaTimerALo, (uchar) timerA);
	/* CIA Timer A hi */
	outp(cia+ciaTimerAHi, (uchar) (timerA >> 8));
	/* Start CIA Timer A */
	outp(cia+ciaCtrlRegA, latch);
}
