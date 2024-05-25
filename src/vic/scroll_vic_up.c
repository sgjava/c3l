/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>

/*
 * Scroll line up given x1, y1, x2, y2 rectangle in current page.
 */
void scrollVicUp(const screen *scr, const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2) {
	/* If line is screen width use optimized  */
	if (x2 - x1 + 1 == scr->scrWidth) {
		scrollVicUpY(scr, y1, y2);
	} else {
		unsigned int scrOfs = (y1 * scr->scrWidth) + (unsigned int) scr->scrMem + x1;
		unsigned char len = x2 - x1 + 1;
		unsigned char lines = y2 - y1;
		scrollVicUpAsm(scrOfs, len, lines);
	}
}
