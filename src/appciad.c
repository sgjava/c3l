/*
 * C128 6526 CIA functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <sys.h>

/*
 * Enable CIA 2 interrupts.
 */
void doneCia() {
	/* Enable CIA 1 IRQ */
	outp(cia1Icr, ciaEnableIrq);
}
