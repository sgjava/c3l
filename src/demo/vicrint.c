/*
 * C128 CP/M C Library C3L
 *
 * VIC raster interrupt replacement demo. Not working at this time.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <hitech.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>

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
	vicRas();
}

/*
 * Set VIC raster interrupt address.
 */
void setInt(ushort address) {
	ushort *intVec = (ushort*) 0xfffe;
#asm
	di
#endasm
	/* This will disable CIA 1 and CIA 2 interrupts */
	initCia();
	intVec[0] = address;
	/* Raster interrupt in line 52 */
	outp(vicRaster, 0x34);
	/* Clear the High bit (lines 256-318) */
	outp(vicCtrlReg1, 0x1b);
	/* Ack any previous raster interrupt */
	outp(vicIntFlag, 0xff);
	/* Enable raster interrupt */
	outp(vicIntMask, 0x01);
#asm
	ei
#endasm
}

/*
 * Disable VIC raster interrupt.
 */
void disableInt() {
#asm
	di
#endasm
	/* Disable raster interrupt */
	outp(vicIntMask, 0x00);
	/* Ack any previous raster interrupt */
	outp(vicIntFlag, 0xff);
#asm
	ei
#endasm
}

/*
 * Replace VIC raster interrupt to rotate VIC border color.
 */
void rasInt(uchar *memEnd) {
	ushort i, found;
	uchar *memStart = (uchar*) 0x0100, saveCtrlReg;
	/* This is the z80 signature used to find the custom interrupt code for vicRas */
	static uchar target[] = { 0xf5, 0xc5, 0x01, 0x20, 0xd0 };
	printf("\nProgram start %04x, end %04x\n", memStart, memEnd);
	/* Find custom interrupt code in program */
	found = findBytes(target, memStart, memEnd - memStart, sizeof(target))
			+ (ushort) memStart;
	/* Make sure we find target code, but not target array */
	if (found != (ushort) target) {
		printf("\n\nFound target at offset %04x\n", found);
		for (i = 0; i < 19; ++i) {
			printf("%02x ", memStart[found + i]);
		}
		setVicMmuBank(1);
		saveCtrlReg = inp(vicCtrlReg1);
		/* Enable screen */
		outp(vicCtrlReg1, ((inp(vicCtrlReg1) | 0x10) & 0x7f));
		/* New interrupt routine */
		setInt(found);
		/* Do something while interrupt is running */
		for (i = 0; i < 30000; ++i) {
		}
		/* Disable raster interrupt */
		disableInt();
		/* Disable screen */
		outp(vicCtrlReg1, saveCtrlReg);
	} else {
		printf("\nTarget not found\n");
	}
}

main() {
	uchar *memEnd = (uchar*) malloc(1);
	/* Only needed this to get end of program memory address */
	free(memEnd);
	rasInt(memEnd);
}
