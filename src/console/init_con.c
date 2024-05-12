/*
 * C128 CP/M console.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>

/*
 * Initialize console.
 */
void initCon(console *con, screen *scr) {
	con->curOn = 0;
	con->curX = 0;
	con->curY = 0;
	con->scr = scr;
	con->curChar = '_';
	con->colorOn = 0;
	con->color = scrWhite;
}
