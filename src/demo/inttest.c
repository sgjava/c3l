/*
 * C128 CP/M C Library C3L
 *
 * Interrupt replacement demo. This will make VIC border color cycle.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <vic.h>
#include <hitech.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>

/*
 * Do not call this function from C. This is a interrupt handler.
 */
void doNotCall() {
	vicInt();
}

/*
 * Set interrupt address.
 */
void setInt(ushort address) {
	ushort *intVec = (ushort*) 0xfdfe;
#asm
    di
#endasm
	/* Clear CIA 1 ICR status */
	inp(cia1+ciaIcr);
    intVec[0] = address;
#asm
    ei
#endasm
}

/*
 * Use this to find the Z80 signature for custom interrupt code.
 */
ushort findBytes(uchar bytes[], uchar *mem, ushort len, uchar size) {
	ushort i;
	for (i = 0; i <= len - size; i++) {
		if (memcmp(&mem[i], bytes, size) == 0) {
			/* Match found starting at index i */
			return i;
		}
	}
	/* No match found */
	return len;
}

main() {
	/* Main interrupt vector is at 0xfdfd which contains a jmp opcode */
	ushort *intVec = (ushort*) 0xfdfe, i, found, address = intVec[0];
	/* Use pointer at 0xfdfe to locate interrupt code */
	uchar *memStart = (uchar*) 0x0100, *memEnd = (uchar*) malloc(1);
	/* This is the z80 signature used to find the custom interrupt code for vicInt */
	static uchar target[] = { 0xf5, 0xc5, 0x01, 0x0d, 0xdc };
	/* Only needed this to get end of program memory address */
	free(memEnd);
	printf("CIA 1 Ctrl Reg A %02x, B %02x\n", inp(cia1 + ciaCtrlRegA),
			inp(cia1 + ciaCtrlRegB));
	printf("CIA 1 Timer A %02x%02x, B %02x%02x\n", inp(cia1 + ciaTimerAHi),
			inp(cia1 + ciaTimerBLo), inp(cia1 + ciaTimerAHi),
			inp(cia1 + ciaTimerBLo));
	printf("Program start %04x, end %04x, interrupt vector %04x\n", memStart,
			memEnd, address);
	/* Find custom interrupt code in program */
	found = findBytes(target, memStart, memEnd - memStart, sizeof(target));
	printf("\n\nFound target at offset %04x\n", found);
	for (i = 0; i < 19; ++i) {
		printf("%02x ", memStart[found + i]);
	}
	/* Enable screen */
	outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
	/* New interrupt routine */
	setInt(found + 0x0100);
	/* Do something while interrupt is running */
	for (i = 0; i < 30000; ++i) {
	}
	/* Old interrupt routine */
	setInt(address);
}
