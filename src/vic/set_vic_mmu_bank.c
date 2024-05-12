/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <stdlib.h>
#include <mmu.h>

/*
 * Set VIC to MMU bank 0 or 1.
 */
void setVicMmuBank(unsigned char mmuRcr) {
	// I/O
	outp(0x0ff00, 0x7e);
	/* If bank 1 then set bit 6 of RCR */
	if (mmuRcr) {
		outp(mmuRamCfg, inp(mmuRamCfg) | 0x40);
	} else {
		outp(mmuRamCfg, inp(mmuRamCfg) & 0xbf);
	}
	// ROM/RAM
	outp(0x0ff00, 0x7f);
}
