/*
 * C128 CP/M console print.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <screen.h>
#include <string.h>

/*
 * Print to console.
 */
void printCon(console *con, char *str) {
	screen *scr = con->scr;
	unsigned int scrOfs;
	scrollCon(con, str);
	if (con->colorOn) {
		(scr->printCol)(scr, con->curX, con->curY, con->color, str);
	} else {
		(scr->print)(scr, con->curX, con->curY, str);
	}
	/* Calculate new cursor position */
	scrOfs = offsetCon(con) + strlen(str);
	/* Advance cursor */
	setCurCon(con, scrOfs);
	/* Display cursor if enabled */
	if (con->curOn) {
		char cursor[2];
		cursor[0] = con->curChar;
		cursor[1] = 0x00;
		if (con->colorOn) {
			(scr->printCol)(scr, con->curX, con->curY, con->color, cursor);
		} else {
			(scr->print)(scr, con->curX, con->curY, cursor);
		}
	}
}
