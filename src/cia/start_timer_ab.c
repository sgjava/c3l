/*
 * C128 6526 CIA functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <stdlib.h>

/*
 * Set CIA count down timers. Timer B counts timer A.
 */
void startTimerAB(unsigned int cia, unsigned int timerA, unsigned int timerB,
		unsigned char latch) {
	// CIA Timer A lo
	outp(cia + ciaTimerALo, (unsigned char ) timerA);
	// CIA Timer A hi
	outp(cia + ciaTimerAHi, (unsigned char ) (timerA >> 8));
	// CIA Timer B lo
	outp(cia + ciaTimerBLo, (unsigned char ) timerB);
	// CIA Timer B hi
	outp(cia + ciaTimerBHi, (unsigned char ) (timerB >> 8));
	// Link time to count and enable timer
	outp(cia + ciaCtrlRegB, latch);
}
