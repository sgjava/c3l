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
 * Get standard or extended key code for single row. 0xff is returned if no key
 * pressed. keyRow is 0 - 10.
 */
unsigned char getKey(unsigned char keyRow) {
	static unsigned char keyCol[8] = { 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf,
			0x7f };
	unsigned char keyCode;
	// Standard keys?
	if (keyRow < 8) {
		outp(vicExtKey, 0xff);
		outp(cia1+ciaDataA, keyCol[keyRow]);
		keyCode = inp(cia1+ciaDataB);
	} else {
		// Extended keys
		outp(cia1+ciaDataA, 0xff);
		outp(vicExtKey, keyCol[keyRow - 8]);
		keyCode = inp(cia1+ciaDataB);
	}
	return keyCode;
}
