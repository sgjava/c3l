/*
 * C128 6526 CIA functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <sys.h>

/*
 * Configure CIA to kill interrupts and enable keyboard scan.
 */
void initCia() {
	/* Clear all CIA 1 IRQ enable bits */
	outp(cia1+ciaIcr, ciaClearIcr);
	/* Clear CIA 1 ICR status */
	inp(cia1+ciaIcr);
	/* Clear all CIA 2 IRQ enable bits */
	outp(cia2+ciaIcr, ciaClearIcr);
	/* Clear CIA 2 ICR status */
	inp(cia2+ciaIcr);
	/* Set CIA 1 DDRs for keyboard scan */
	outp(cia1+ciaDdrA, 0xff);
	outp(cia1+ciaDdrB, 0x00);
}
