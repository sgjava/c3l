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
 * Print to console.
 */
void printCon(console *con, char *str) {
	screen *scr = con->scr;
	ushort scrOfs;
	scrollCon(con, str);
	(scr->print)(scr, con->curX, con->curY, str);
	/* Calculate new cursor position */
	scrOfs = con->curY * scr->scrWidth + con->curX + strlen(str);
	/* Advance cursor */
	con->curY = scrOfs / scr->scrWidth;
	con->curX = scrOfs - (con->curY * scr->scrWidth);
	/* Display cursor if enabled */
	if (con->curOn) {
		char cursor[2];
		cursor[0] = con->curChar;
		cursor[1] = 0x00;
		(scr->print)(scr, con->curX, con->curY, cursor);
	}
}
