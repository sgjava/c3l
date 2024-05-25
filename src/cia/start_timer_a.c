/*
 * C128 6526 CIA functions.
 *
 * Start CIA timer A.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <stdlib.h>

/*
 Start CIA timer A using Hz value and latch for mode.
 */
void startTimerA(const unsigned int cia, const unsigned int hz, const unsigned char latch) {
	unsigned int timerA = ciaTimerFreq / hz;
	// CIA Timer A lo
	outp(cia+ciaTimerALo, timerA);
	// CIA Timer A hi
	outp(cia+ciaTimerAHi, (timerA >> 8));
	// Start CIA Timer A
	outp(cia+ciaCtrlRegA, latch);
}
