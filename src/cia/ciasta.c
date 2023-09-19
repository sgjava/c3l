/*
 * C128 6526 CIA functions.
 *
 * Set CIA TOD clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 Start CIA 2 timer A in continuous mode using Hz value.
 */
void startTimer(ushort cia, ushort hz) {
	ushort timerA = ciaTimerFreq / hz;
	/* CIA Timer A lo */
	outp(cia+ciaTimerALo, (uchar) timerA);
	/* CIA Timer A hi */
	outp(cia+ciaTimerAHi, (uchar) (timerA >> 8));
	/* Start CIA Timer A */
	outp(cia+ciaCtrlRegA, ciaCpuCont);
}
