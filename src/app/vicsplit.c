/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe split screen bitmap/text  demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <cia.h>
#include <console.h>
#include <demo.h>
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vic.h>

/*
 * Use this to find the Z80 signature for custom interrupt code. len is returned
 * if byte sequence not found.
 */
unsigned int findBytes(unsigned char bytes[], unsigned char *mem, unsigned int len, unsigned char size) {
	unsigned int i;
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
 * Initialize key scan, screen and bitmap.
 */
void init(console *con, screen *scr, bitmap *bmp) {
	initCia();
	/* Use ram at end of bank 1 for text and bitmap */
	initVicScr(scr, 0x8800, 0x8000);
	initVicScrMode(scr, scrBlue, scrBlack, scrWhite);
	initCon(con, scr);
	initVicBmp(bmp, 0xa000, 0x8c00, 0x8000);
	/* Clear bitmap */
	(bmp->clearBmp)(bmp, 0);
	/* Set foreground and background pixel colors */
	(bmp->clearBmpCol)(bmp,
			(bmp->color[bmpWhite] << 4) | (bmp->color[bmpBlack] & 0x0f));
}

/*
 * Restore VIC back to CP/M defaults.
 */
void done() {
	doneVic();
	doneCia();
}

/*
 * Find IRQ code signature and run demo. If assembler code changes then signature must change as well.
 */
void run(unsigned char *memEnd, console *con, bitmap *bmp) {
	extern void *irq1;
	unsigned int found;
	unsigned char *memStart = (unsigned char*) 0x0100;
	/* This is the z80 signature used to find the custom interrupt code inside vicSplitScr */
	static unsigned char target[] = { 0xf5, 0xc5, 0xe5, 0x01, 0x12, 0xd0 };
	/* Find custom interrupt code in program */
	found = findBytes(target, memStart, memEnd - memStart, sizeof(target))
			+ (unsigned int) memStart;
	/* Make sure we find target code, but not target array */
	if (found != (unsigned int) target) {
		runGraphDemoI(con, bmp, found);
	} else {
		printf("\nIRQ code signature not found\n");
	}
}

main() {
	/* Use ram in bank 2 */
	unsigned char *vicMem = allocVicMem(2);
	/* Create screen struct */
	screen *scr = (screen*) malloc(sizeof(screen));
	/* Create console struct */
	console *con = (console*) malloc(sizeof(console));
	/* Create bitmap struct */
	bitmap *bmp = (bitmap*) malloc(sizeof(bitmap));
	init(con, scr, bmp);
	run(vicMem - 1, con, bmp);
	done();
	/* Free memory */
	free(vicMem);
}
