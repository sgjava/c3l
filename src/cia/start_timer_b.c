/*
 * C128 6526 CIA functions.
 *
 * Start CIA timer B.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <stdlib.h>

/*
 Start CIA timer B using Hz value and latch for mode.
 */
void startTimerB(unsigned int cia, unsigned int hz, unsigned char latch) {
	unsigned int timerB = ciaTimerFreq / hz;
	// CIA Timer B lo
	outp(cia+ciaTimerBLo, (unsigned char ) timerB);
	// CIA Timer B hi
	outp(cia+ciaTimerBHi, (unsigned char ) (timerB >> 8));
	// Start CIA Timer B
	outp(cia+ciaCtrlRegB, latch);
}
