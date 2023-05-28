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
printCon(console *con, char *str) {
	screen *scr = con->scr;
	ushort scrOfs;
	scrollCon(con, str);
	(scr->print)(scr, con->curX, con->curY, str);
	/* Calculate new cursor position */
	scrOfs = con->curY * scr->scrWidth + con->curX + strlen(str);
	con->curY = scrOfs / scr->scrWidth;
	con->curX = scrOfs - (con->curY * scr->scrWidth);
}
