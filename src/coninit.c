/*
 * C128 CP/M console.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <hitech.h>

/*
 * Initialize console.
 */
void initCon(console *con, screen *scr) {
	con->curX = 0;
	con->curY = 0;
	con->scr = scr;
}
