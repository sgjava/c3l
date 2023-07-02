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
 * Print to console and set cursor to next line.
 */
void printLineCon(console *con, char *str) {
	screen *scr = con->scr;
	printCon(con, str);
	/* Remove cursor if enabled */
	if (con->curOn) {
		(scr->print)(scr, con->curX, con->curY, " ");
	}
	con->curX = 0;
	if (con->curY < scr->scrHeight - 1) {
		con->curY++;
	} else {
		if (con->colorOn) {
			(scr->scrollUpCol)(scr, 0, 0, scr->scrWidth - 1,
					scr->scrHeight - 1);
		} else {
			(scr->scrollUp)(scr, 0, 0, scr->scrWidth - 1, scr->scrHeight - 1);
		}
		(scr->fillMem)(scr->scrMem + scr->scrSize - scr->scrWidth,
				scr->scrWidth, 32);
	}
}
