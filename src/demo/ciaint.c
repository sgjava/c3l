/*
 * C128 CP/M C Library C3L
 *
 * CIA interrupt replacement demo. This will make VIC border color cycle.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>
#include <vic.h>

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

/*
 * Do not call this function from C. This is a interrupt handler.
 */
void doNotCall() {
	vicInt();
}

/*
 * Set CIA 1 interrupt address.
 */
void setInt(ushort address) {
	ushort *intVec = (ushort*) 0xfdfe;
#asm
	di
#endasm
	/* Clear CIA 1 ICR status */
	inp(cia1 + ciaIcr);
	intVec[0] = address;
#asm
	ei
#endasm
}

/*
 * Replace CIA 1 interrupt to rotate VIC border color.
 */
void ciaInt(uchar *memEnd) {
	/* Main interrupt vector is at 0xfdfd which contains a jmp opcode */
	ushort *intVec = (ushort*) 0xfdfe, address = intVec[0], i, found;
	uchar *memStart = (uchar*) 0x0100, saveCtrlReg, saveBorder;
	/* This is the z80 signature used to find the custom interrupt code for vicInt */
	static uchar target[] = { 0xf5, 0xc5, 0x01, 0x0d, 0xdc };
	printf("\nCIA 1 Ctrl Reg A %02x, B %02x\n", inp(cia1 + ciaCtrlRegA),
			inp(cia1 + ciaCtrlRegB));
	printf("CIA 1 Timer A %02x%02x, B %02x%02x\n", inp(cia1 + ciaTimerAHi),
			inp(cia1 + ciaTimerBLo), inp(cia1 + ciaTimerAHi),
			inp(cia1 + ciaTimerBLo));
	printf("Program start %04x, end %04x, interrupt vector %04x\n", memStart,
			memEnd, address);
	/* Find custom interrupt code in program */
	found = findBytes(target, memStart, memEnd - memStart, sizeof(target))
			+ (ushort) memStart;
	/* Make sure we find target code, but not target array */
	if (found != (ushort) target) {
		printf("\n\nFound target at %04x\n", found);
		for (i = 0; i < 19; ++i) {
			printf("%02x ", memStart[found + i]);
		}
		saveCtrlReg = inp(vicCtrlReg1);
		saveBorder = inp(vicBorderCol);
		/* Enable screen */
		outp(vicCtrlReg1, ((saveCtrlReg | 0x10) & 0x7f));
		/* New interrupt routine */
		setInt(found);
		/* Do something while interrupt is active */
		for (i = 0; i < 30000; ++i) {
		}
		outp(vicBorderCol, saveBorder);
		/* Disable screen */
		outp(vicCtrlReg1, saveCtrlReg);
		/* Old interrupt routine */
		setInt(address);
	} else {
		printf("\nTarget not found\n");
	}
}

main() {
	uchar *memEnd = (uchar*) malloc(1);
	/* Only needed this to get end of program memory address */
	free(memEnd);
	ciaInt(memEnd);
}
