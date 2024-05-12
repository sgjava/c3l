/*
 * C128 6526 CIA functions.
 *
 * Keys are mapped the same as getch for the most part.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <stdlib.h>

/*
 * Get all standard and extended key rows.
 */
void getKeys(unsigned char *ciaKeyScan) {
	static unsigned char keyCol[8] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf,
			0x7f };
	unsigned char i;
	outp(vicExtKey, 0xff);
	// Scan standard keys
	for (i = 0; i < 8; i++) {
		outp(cia1+ciaDataA, keyCol[i]);
		ciaKeyScan[i] = inp(cia1+ciaDataB);
	}
	outp(cia1+ciaDataA, 0xff);
	// Scan extended keys
	for (i = 0; i < 3; i++) {
		outp(vicExtKey, keyCol[i]);
		ciaKeyScan[i + 8] = inp(cia1+ciaDataB);
	}
}
