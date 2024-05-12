/*
 * C128 CP/M console print.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <screen.h>
#include <string.h>

/*
 * Scroll and update cursor position based on string length.
 */
void scrollCon(console *con, char *str) {
	screen *scr = con->scr;
	unsigned int scrOfs = offsetCon(con);
	unsigned int len = strlen(str);
	/* Do we need to scroll? */
	if (scrOfs + len > scr->scrSize) {
		unsigned char y = (scrOfs + len - scr->scrSize) / scr->scrWidth + 1;
		/* First scroll, so bottom line can be blanked */
		if (con->colorOn) {
			(scr->scrollUpCol)(scr, 0, 0, scr->scrWidth - 1,
					scr->scrHeight - 1);
		} else {
			(scr->scrollUp)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
		}
		(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth,
				scr->scrWidth, 32);
		scrOfs = scrOfs - (y * scr->scrWidth);
		y -= 1;
		/* Scroll Y lines */
		for (; y > 0; y--) {
			if (con->colorOn) {
				(scr->scrollUpCol)(scr, 0, 0, scr->scrWidth - 1,
						scr->scrHeight - 1);
			} else {
				(scr->scrollUp)(scr, 0, 0, scr->scrWidth - 1,
						scr->scrHeight - 1);
			}
		}
		/* Set new cursor position for print */
		setCurCon(con, scrOfs);
	}
}
