/*
 * C128 CP/M C Library C3L
 *
 * Baseline program to show minimum compile size.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <stdio.h>
#include <sys.h>

/*
 * Set VIC bank to 0 - 3.
 */
void setVicBank(uchar vicBank) {
	uchar saveDdr = inp(0xdd02);
	/* Set DDR port A to write */
	outp(0xdd02, inp(0xdd02) | 0x03);
	/* Set VIC to bank 0-3 */
	outp(0xdd00, (inp(0xdd00) & 0xfc) | (3 - vicBank));
	outp(0xdd02, saveDdr);
}

main() {
	uchar bank;
	ushort i;
	uchar *forceMap = (uchar*) 0xff00;
	printf("Force map: %04x, bank 0: %04x, bank 1: %04x, io 0: %04x, io 1: %04x\n", forceMap[0], forceMap[1], forceMap[2], forceMap[3], forceMap[4]);
	/* Enable VIC screen */
    outp(0xd011, inp(0xd011) | 0x10);
    /* I/O */
    forceMap[0] = 0x7e;
    /* VIC MMU bank 1 */
    outp(0xd506, (inp(0xd506) & 0xbf) | 0x40);
    /* ROM/RAM */
    forceMap[0] = 0x7f;
    /* Set VIC 16K bank */
    for (bank = 0; bank < 4; ++bank) {
    	printf("VIC bank: %d\n", bank);
        setVicBank(bank);
        for (i = 0; i < 20000; ++i) {
    	}
	}
    /* ROM/RAM */
    forceMap[0] = 0x7e;
    /* VIC MMU bank 0 */
    outp(0xd506, inp(0xd506) & 0xbf);
    /* ROM/RAM */
    forceMap[0] = 0x7f;
    setVicBank(0);
}
