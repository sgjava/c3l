/*
 * C128 CP/M 8564/8566 VIC-IIe general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sys.h>

/*
 * Set VIC bank to 0 - 3.
 */
void setVicBank(uchar vicBank) {
	uchar saveDdr = inp(cia2DdrA);
	/* Set DDR port A to write */
	outp(cia2DdrA, inp(cia2DdrA) | 0x03);
	/* Set VIC to bank 0-3 */
	outp(cia2DataA, (inp(cia2DataA) & 0xfc) | (3 - vicBank));
	outp(cia2DdrA, saveDdr);
}
