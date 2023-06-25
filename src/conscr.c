/*
 * C128 CP/M console print.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <hitech.h>
#include <screen.h>
#include <string.h>

/*
 * Scroll and update cursor position based on string length.
 */
void scrollCon(console *con, char *str) {
	screen *scr = con->scr;
	ushort scrOfs = con->curY * scr->scrWidth + con->curX;
	ushort len = strlen(str);
	/* Do we need to scroll? */
	if (scrOfs + len > scr->scrSize) {
        uchar y = (scrOfs + len - scr->scrSize) / scr->scrWidth + 1;
        /* First scroll, so bottom line can be blanked */
        (scr->scrollUp)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
		(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth, scr->scrWidth,
				32);
        scrOfs = scrOfs - (y * scr->scrWidth);
        y -= 1;
        /* Scroll Y lines */
		for (; y > 0; y--) {
			(scr->scrollUp)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
		}
		/* Set new cursor position for print */
		con->curY = scrOfs / scr->scrWidth;
		con->curX = scrOfs - (con->curY * scr->scrWidth);
	}
}
