/*
 * C128 CP/M C Library C3L
 *
 * Interrupt demo. I leave the CIA 1 timer interrupt in place and just change
 * the code it executes to change the VIC border color. Then I use the VIC raster
 * interrupt to change just a portion of the VIC border.
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
 * Use this to find the Z80 signature for custom interrupt code. len is returned
 * if byte sequence not found.
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
 * Do not call this function from C. This function is used to include our Z80
 * assembler code which is located with findBytes.
 */
void doNotCall() {
	vicInt();
	vicRas();
}

/*
 * Set CIA 1 interrupt address.
 */
void setCiaInt(ushort address) {
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
	printf("\nProgram start %04x, end %04x, interrupt vector %04x\n", memStart,
			memEnd, address);
	/* Find custom interrupt code in program */
	found = findBytes(target, memStart, memEnd - memStart, sizeof(target))
			+ (ushort) memStart;
	/* Make sure we find target code, but not target array */
	if (found != (ushort) target) {
		printf("\nFound CIA 1 target at %04x\n", found);
		for (i = 0; i < 19; ++i) {
			printf("%02x ", memStart[found - (ushort) memStart + i]);
		}
		saveCtrlReg = inp(vicCtrlReg1);
		saveBorder = inp(vicBorderCol);
		/* Enable screen */
		outp(vicCtrlReg1, ((saveCtrlReg | 0x10) & 0x7f));
		/* New interrupt routine */
		setCiaInt(found);
		/* Do something while interrupt is active */
		for (i = 0; i < 30000; ++i) {
		}
		outp(vicBorderCol, saveBorder);
		/* Disable screen */
		outp(vicCtrlReg1, saveCtrlReg);
		/* Old interrupt routine */
		setCiaInt(address);
	} else {
		printf("\nTarget not found\n");
	}
}

/*
 * Set VIC raster interrupt address.
 */
void setVicInt(ushort address) {
	ushort *intVec = (ushort*) 0xfdfe;
#asm
	di
#endasm
	/* Clear all CIA 1 IRQ enable bits */
	outp(cia1+ciaIcr, ciaClearIcr);
	/* Clear CIA 1 ICR status */
	inp(cia1+ciaIcr);
	/* Clear all CIA 2 IRQ enable bits */
	outp(cia2+ciaIcr, ciaClearIcr);
	/* Clear CIA 2 ICR status */
	inp(cia2+ciaIcr);
	intVec[0] = address;
	/* Raster interrupt line */
	outp(vicRaster, 151);
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
void disableVicInt(ushort address) {
	ushort *intVec = (ushort*) 0xfdfe;
#asm
	di
#endasm
	/* Disable raster interrupt */
	outp(vicIntMask, 0x00);
	/* Ack any previous raster interrupt */
	outp(vicIntFlag, 0xff);
	intVec[0] = address;
#asm
	ei
#endasm
}

/*
 * Replace VIC raster interrupt to rotate VIC border color.
 */
void rasInt(uchar *memEnd) {
	ushort *intVec = (ushort*) 0xfdfe, address = intVec[0], i, found;
	uchar *memStart = (uchar*) 0x0100, saveCtrlReg, saveBorder;
	/* This is the z80 signature used to find the custom interrupt code for vicRas */
	static uchar target[] = { 0xf5, 0xc5, 0x01, 0x12, 0xd0, 0xed, 0x78, 0xfe, 0x97 };
	/* Find custom interrupt code in program */
	found = findBytes(target, memStart, memEnd - memStart, sizeof(target))
			+ (ushort) memStart;
	/* Make sure we find target code, but not target array */
	if (found != (ushort) target) {
		printf("\n\nFound VIC raster target at %04x\n", found);
		for (i = 0; i < 19; ++i) {
			printf("%02x ", memStart[found - (ushort) memStart + i]);
		}
		/* setVicMmuBank(1); */
		saveCtrlReg = inp(vicCtrlReg1);
		saveBorder = inp(vicBorderCol);
		/* Enable screen */
		outp(vicCtrlReg1, ((inp(vicCtrlReg1) | 0x10) & 0x7f));
		/* New interrupt routine */
		setVicInt(found);
		/* Do something while interrupt is running */
		for (i = 0; i < 30000; ++i) {
		}
		/* Disable raster interrupt */
		disableVicInt(address);
		outp(vicBorderCol, saveBorder);
		/* Disable screen */
		outp(vicCtrlReg1, saveCtrlReg);
	} else {
		printf("\nTarget not found\n");
	}
}

main() {
	/* Only needed this to get end of program memory address */
	uchar *memEnd = (uchar*) malloc(1);
	free(memEnd);
	ciaInt(memEnd-1);
	rasInt(memEnd-1);
}
