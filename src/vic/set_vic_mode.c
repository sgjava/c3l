/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <vic.h>

/*
 * Set ecm, bmm and mcm to 0 (off) or 1 (on).
 */
void setVicMode(unsigned char ecm, unsigned char bmm, unsigned char mcm) {
	/* Set enhanced color and char/bitmap mode */
	outp(vicCtrlReg1,
			(inp(vicCtrlReg1) & 0x9f) | ((ecm * 0x40) + (bmm * 0x20)));
	/* Set multicolor mode */
	outp(vicCtrlReg2, (inp(vicCtrlReg2) & 0xef) | (mcm * 0x10));
}
