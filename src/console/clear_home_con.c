/*
 * C128 CP/M console clear screen.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <screen.h>

/*
 * Clear screen, color and home cursor.
 */
void clearHomeCon(const console *con) {
	/* Clear screen to spaces */
	(con->scr->clearScr)(con->scr, 32);
	/* Clear color to white */
	(con->scr->clearScrCol)(con->scr, scrWhite);
	/* Home console cursor */
	con->curX = 0;
	con->curY = 0;
}
