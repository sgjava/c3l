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
	uchar saveDdr = inp(cia2+ciaDdrA);
	/* Set DDR port A to write */
	outp(cia2+ciaDdrA, inp(cia2+ciaDdrA) | 0x03);
	/* Set VIC to bank 0-3 */
	outp(cia2+ciaDataA, (inp(cia2+ciaDataA) & 0xfc) | (3 - vicBank));
	outp(cia2+ciaDdrA, saveDdr);
}
