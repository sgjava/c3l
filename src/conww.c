/*
 * C128 CP/M console print.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <hitech.h>
#include <string.h>

void wordWrap(console *con, char *str) {
	/* Screen width should not exceed buffer size +1 */
	char buffer[81];
	ushort i = 0, len = strlen(str);
	uchar maxLine = con->scr->scrWidth, wordStart = 0, buf = 0,
			curX = con->curX;
	while (curX < maxLine && i < len) {
		while (curX < maxLine && i < len) {
			/* Find first non space char */
			if (str[i] != ' ') {
				if (!wordStart) {
					wordStart = i;
				}
				buffer[buf++] = str[i];
				curX++;
			} else {
				/* End of word including space */
				if (wordStart) {
					if (curX < maxLine) {
						buffer[buf++] = str[i];
						curX++;
						wordStart = 0;
					};
				}
			}
			i++;
		}
		if (wordStart && curX == maxLine) {
			buffer[buf-(i-wordStart+1)] = 0x00;
			printLineCon(con, buffer);
			i = wordStart;
			wordStart = 0;
			buf = 0;
			curX = con->curX;
		} else {
			buffer[buf] = 0x00;
			printCon(con, buffer);
			wordStart = 0;
			buf = 0;
			curX = con->curX;
		}
	}
}
