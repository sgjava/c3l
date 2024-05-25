/*
 * C128 CP/M console calculate offset.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>

/*
 * Calculate offset in screen memory based on cursor position.
 */
unsigned int offsetCon(const console *con) {
	return con->curY * con->scr->scrWidth + con->curX;
}
