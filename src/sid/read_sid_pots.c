/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <sid.h>
#include <stdlib.h>

/*
 * Read all pots (values are passed by reference).
 *
 * Note CIA 2 timer A is used.
 */
void readSidPots(const unsigned char *x1, const unsigned char *y1, const unsigned char *x2,
		const unsigned char *y2) {
	unsigned char saveReg = inp(cia1 + ciaDdrA);
	// Set bits 6 and 7 to output
	outp(cia1 + ciaDdrA, ciaPots);
	// Set 4066 to read port 1 pots
	outp(cia1 + ciaDataA, ciaPotsPort1);
	// Clear all CIA 2 IRQ enable bits
	outp(cia2+ciaIcr, ciaClearIcr);
	// 1.6 ms (625 Hz) delay to get stable reading
	startTimerA(cia2, 625, ciaCpuOne);
	while ((inp(cia2 + ciaIcr) & 0x01) == 0)
		;
	// Read pots
	*x1 = inp(sidPotX);
	*y1 = inp(sidPotY);
	// Set 4066 to read port 2 pots
	outp(cia1 + ciaDataA, ciaPotsPort2);
	// Clear all CIA 2 IRQ enable bits
	outp(cia2+ciaIcr, ciaClearIcr);
	// 1.6 ms (625 Hz) delay to get stable reading
	startTimerA(cia2, 625, ciaCpuOne);
	while ((inp(cia2 + ciaIcr) & 0x01) == 0)
		;
	// Read pots
	*x2 = inp(sidPotX);
	*y2 = inp(sidPotY);
	// Restore data dir reg
	outp(cia1 + ciaDdrA, saveReg);
}
