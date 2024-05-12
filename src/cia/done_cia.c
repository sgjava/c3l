/*
 * C128 6526 CIA functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <stdlib.h>

/*
 * Enable CIA 1 interrupts.
 */
void doneCia() {
	// Enable CIA 1 IRQ
	outp(cia1+ciaIcr, ciaEnableIrq);
}
