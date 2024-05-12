/*
 * C128 CP/M console print.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <console.h>
#include <string.h>

void printWrapCon(console *con, char *str) {
	/* Screen width should not exceed buffer size +1 */
	char buffer[81];
	unsigned int i = 0, wordLen, len = strlen(str);
	int wordStart = -1, wordEnd = -1;
	unsigned char maxLine = con->scr->scrWidth - 1, buf = 0, maxBuf = sizeof(buffer)
			- 1;
	while (i < len && buf < maxBuf) {
		/* Load word buffer using space delimiter */
		while (i < len && wordEnd < 0 && buf < maxBuf) {
			/* Find first non space char */
			if (str[i] != ' ') {
				if (wordStart < 0) {
					wordStart = i;
				}
				buffer[buf++] = str[i];
			} else {
				/* End of word including space */
				if (wordEnd < 0) {
					buffer[buf++] = str[i];
					wordEnd = i;
				};
			}
			i++;
		}
		if (buf > 0) {
			buffer[buf] = 0x00;
			wordLen = strlen(buffer);
			if (con->curX + wordLen > maxLine) {
				printLineCon(con, "");
			}
			printCon(con, buffer);
			wordStart = -1;
			wordEnd = -1;
			buf = 0;
		}
	}
}
