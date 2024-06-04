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
 * Wait for Return.
 */
void bitmapWaitKey(const bitmap *bmp) {
	(bmp->printBmp)(bmp, 0, bmp->scrHeight - 1, " Press Return ");
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	/* Debounce */
	while (getKey(0) == 0xfd)
		;
}

/*
 * Draw Bezier.
 */
void bezier(const bitmap *bmp, const int x, const int y, const int w, const int h, const unsigned char count) {
	unsigned char i, color = 1;
	for (i = 0; i < count; i++) {
		drawBezier(bmp, (i * 2) + x + 3, y + 3, x + (w / 2), (i * 3) + y, x + w - 3, (i * 4) + y, color++);
		if (color > 3) {
			color = 1;
		}
	}
}

/*
 * Draw circles.
 */
void circles(const bitmap *bmp, const int x, const int y, const unsigned char count) {
	unsigned char i, color = 1;
	int x0, y0;
	for (i = 0; i < count; i++) {
		drawCircle(bmp, x, y, i * 5 + 10, color++);
		if (color > 3) {
			color = 1;
		}
	}
}

/*
 * Draw horizontal lines.
 */
void horzLines(const bitmap *bmp, const int x, const int y, const unsigned char count) {
	unsigned char i, color = 1;
	for (i = 0; i < count; i++) {
		drawLine(bmp, x, y + i, bmp->bmpWidth - 1, y + i, color++);
		if (color > 3) {
			color = 1;
		}
	}
}

/*
 * Run demo.
 */
void run(const bitmap *bmp) {
	bezier(bmp, 0, 0, bmp->bmpWidth - 1, bmp->bmpHeight - 1, 14);
	circles(bmp, bmp->bmpWidth / 2, bmp->bmpHeight / 2, 10);
	horzLines(bmp, 0, bmp->bmpHeight - 50, 10);
	bitmapWaitKey(bmp);
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
