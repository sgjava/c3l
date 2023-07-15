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
	uchar *forceMap = (uchar*) 0xff00;
    /* MMU I/O bit to allow Z80 IN/OUT to work */
    forceMap[0] = 0x7e;
	/* Set MMU RCR bit 6 to point VIC to MMU bank */
	outp(mmuRamCfg, (inp(mmuRamCfg) & 0xbf) | (mmuRcr * 0x40));
    /*  MMU I/O bit set to ROM/RAM */
    forceMap[0] = 0x7f;
}
