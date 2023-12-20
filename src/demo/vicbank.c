/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe sprite demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>
#include <vdc.h>
#include <vic.h>

/*
 * Initialize key scan and screen.
 */
void init(uchar vicBank) {
	initCia();
	saveVic();
	/* Enable screen */
	outp(vicCtrlReg1, ((inp(vicCtrlReg1) | 0x10) & 0x7f));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done() {
	doneVic();
	doneCia();
}

/*
 * Wait for Return key to be pressed.
 */
void waitKey(uchar *scrMem, uchar x, uchar y, char *str) {
	ushort scrOfs = (y * 40) + x;
	ushort len = strlen(str);
	ushort i;
	for (i = 0; i < len; i++) {
		scrMem[scrOfs + i] = str[i];
	}
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
 * Run demo.
 */
void run(uchar vicBank) {
	uchar i, charVal = 48;
	uchar *scrMem = (uchar*) (vicBank * 16384), *chrMem = (uchar*) ((vicBank
			* 16384) + (7 * 2048));
	setVicChrMem(7);
	/* Copy VDC alt char set to VIC mem */
	copyVdcChrMem(chrMem, 0x3000, 256);
	fillVicMemCol(vicColMem, 1000, vicWhite);
	printf("x");
	for (i = 0; i < 16; i++) {
		/* printf("setVicChrMode\n"); */
		if (i < 14) {
			setVicChrMode(1, vicBank, i, 7);
		} else {
			setVicChrMode(1, vicBank, i, 0);
		}
		if (i == 10) {
			charVal = 55;
			chrMem = (uchar*) ((vicBank * 16384) + (0 * 2048));
			setVicChrMem(0);
			copyVdcChrMem(chrMem, 0x3000, 256);
		} else if (i == 14) {
			chrMem = (uchar*) ((vicBank * 16384) + (0 * 2048));
			setVicChrMem(0);
			copyVdcChrMem(chrMem, 0x3000, 256);
		}
		fillVicMem(scrMem + (i * 1024), 1000, charVal + i);
		waitKey(scrMem + (i * 1024), 0, 24, "Press Return");
	}
}

main() {
	/* VIC bank 1 */
	uchar *vicMem = allocVicMem(1);
	init(1);
	run(1);
	done();
	/* Free memory */
	free(vicMem);
}
