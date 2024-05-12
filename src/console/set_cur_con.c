/*
 * C128 CP/M console calculate offset.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>

/*
 * Set cursor position based on screen offset.
 */
void setCurCon(console *con, unsigned int offset) {
	con->curY = offset / con->scr->scrWidth;
	con->curX = offset - (con->curY * con->scr->scrWidth);
}
