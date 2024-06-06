/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <bitmap.h>
#include <stdlib.h>
#include <stdio.h>
#include <vic.h>
#include <vdc.h>
#include <mmu.h>
#include <demo.h>

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024
// Protect VIC memory < 0x8000
#pragma output CRT_HEAP_ADDRESS = 0x8000

/*
 * Set VIC to MMU bank 0 or 1.
 */
void setVicMmuBankLocal(const unsigned char mmuRcr) {
	/* I/O */
	outp(0x0ff00, 0x7e);
	/* If bank 1 then set bit 6 of RCR */
	if (mmuRcr) {
		outp(mmuRamCfg, inp(mmuRamCfg) | 0x40);
	} else {
		outp(mmuRamCfg, inp(mmuRamCfg) & 0xbf);
	}
	/* ROM/RAM */
	outp(0x0ff00, 0x7f);
}

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void init(const bitmap *bmp) {
	initCia();
	initVicBmpMc(bmp, 0x6000, 0x4800, 0x4000);
	setVicMmuBankLocal(1);
	initVicBmpModeMc(bmp, bmpBlack, bmpLightBlue, bmpWhite, bmpRed, bmpBlue);
}

/*
 * Restore VIC back to CP/M defaults.
 */
void done() {
	restoreVic();
	/* CPM default */
	setVicMmuBankLocal(0);
	setVicBank(0);
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
	doneCia();
}

/*
 * Run demo.
 */
void run(const bitmap *bmp) {
	runGraphDemo(bmp, 2);
}

main() {
	/* Create bitmap struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	init(bmp);
	run(bmp);
	done();
	/* Free memory */
	free(bmp);
}
