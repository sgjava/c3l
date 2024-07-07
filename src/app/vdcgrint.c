/*
 * C128 CP/M C Library C3L
 *
 * 8563 VDC bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <stdlib.h>
#include <vdc.h>

#include "demo.h"

#pragma output noprotectmsdos
#pragma output CRT_STACK_SIZE = 1024

/*
 * Configure CIA, copy fonts to memory, set screen struct for VDC and clear screen.
 */
void init(const bitmap *bmp, const unsigned char *chr) {
	initCia();
	initVdcIntBmp(bmp, vdcScrMem, vdcColMem, chr);
	initVdcIntBmpMode(bmp, chr, bmpBlack, bmpWhite);
}

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void done(const bitmap *bmp, const unsigned char *chr) {
	doneVdc();
	doneCia();
	/* Copy character set from memory to VDC */
	copyVdcMemChr(chr, 0x2000, 512);
}

/*
 * Run demo.
 */
void run(const bitmap *bmp) {
	int i;
	//runGraphDemo(bmp);
	drawLine(bmp, 0, 0, bmp->bmpWidth - 1, 199, bmp->color[bmpWhite]);
	//(bmp->setPixel)(bmp, 0, 0, bmp->color[bmpWhite]);
	/*
	for (i = 0; i < 1000; ++i) {
		bmp->bmpMem[i] = 0xff;
	}
	*/
	// Debounce
	while (getKey(0) == 0xfd)
		;
	while (getKey(0) != 0xfd)
		;
	// Debounce
	while (getKey(0) == 0xfd)
		;
}

main() {
	/* Save both VDC char sets */
	unsigned char *chr = (unsigned char*) malloc(4096);
	/* Create screen struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	init(bmp, chr);
	run(bmp);
	done(bmp, chr);
	/* Free memory */
	free(chr);
	free(bmp);
}
