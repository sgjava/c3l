/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <mmu.h>
#include <sys.h>

/*
 * Set VIC to MMU bank 0 or 1.
 */
void setVicMmuBank(uchar mmuRcr) {
	/* If bank 1 then set bit 6 of RCR */
	if (mmuRcr) {
		vicMmuBank(0x40);
	} else {
		vicMmuBank(0x00);
	}
}
