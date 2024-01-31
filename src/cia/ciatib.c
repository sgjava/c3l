/*
 * C128 6526 CIA functions.
 *
 * Start CIA timer B.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 Start CIA timer B using Hz value and latch for mode.
 */
void startTimerB(ushort cia, ushort hz, uchar latch) {
	ushort timerB = ciaTimerFreq / hz;
	/* CIA Timer B lo */
	outp(cia+ciaTimerBLo, (uchar) timerB);
	/* CIA Timer B hi */
	outp(cia+ciaTimerBHi, (uchar) (timerB >> 8));
	/* Start CIA Timer B */
	outp(cia+ciaCtrlRegB, latch);
}
