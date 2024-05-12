/*
 * C128 CP/M console read line.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <console.h>
#include <screen.h>
#include <stdlib.h>

/*
 * Handle backspace for editing.
 */
void backSpace(console *con) {
	unsigned int scrOfs = offsetCon(con) - 1;
	char printBuf[3];
	printBuf[0] = con->curChar;
	printBuf[1] = ' ';
	printBuf[2] = 0;
	/* Calculate cursor position for backspace */
	setCurCon(con, scrOfs);
	con->curOn = 0;
	printCon(con, printBuf);
	con->curOn = 1;
	/* Calculate new cursor position */
	setCurCon(con, scrOfs);
}

/*
 * Use screen memory as simple input line. Only backspace supported, but insert
 * and delete could be added later.
 */
char* readLineCon(console *con, unsigned char len) {
	screen *scr = con->scr;
	char *str, printBuf[2];
	unsigned char strLen = 0, keyVal, lastKeyVal = 0, curOn = con->curOn, i;
	printBuf[1] = 0;
	/* Make sure cursor is on for input */
	con->curOn = 1;
	printBuf[0] = con->curChar;
	(scr->print)(scr, con->curX, con->curY, printBuf);
	/* Timer A counts milliseconds 48 times or ~1/20 second */
	startTimerAB(cia2, ciaMs, 48, ciaCountA);
	/* Start timer in continuous mode */
	outp(cia2+ciaCtrlRegA, ciaCpuCont);
	do {
		keyVal = decodeKey();
		/* Debounce if current key equals last key */
		if (keyVal == lastKeyVal) {
			i = 0;
			do {
				/* Wait for underflow of ciaTimerBHi */
				while ((inp(cia2+ciaIcr) & 0x02) == 0x00)
					;
				keyVal = decodeKey();
				i++;
			} while ((keyVal == lastKeyVal) && (i < 3));
		}
		lastKeyVal = keyVal;
		/* Decoded key? */
		if (keyVal != 0x00) {
			/* Backspace? */
			if (keyVal == 0x7f) {
				if (strLen > 0) {
					strLen--;
					backSpace(con);
				}
			} else {
				if (keyVal != 0x0d && strLen < len) {
					strLen++;
					printBuf[0] = keyVal;
					printCon(con, printBuf);
				}
			}
		}
	} while (keyVal != 0x0d);
	/* Stop timer */
	outp(cia2+ciaCtrlRegA, ciaStopTimer);
	str = (char*) malloc(strLen + 1);
	/* Screen to string */
	(scr->copyScrToStr)(scr, (con->curY * scr->scrWidth) + con->curX - strLen,
			str, strLen);
	/* Remove cursor from end of input */
	(scr->print)(scr, con->curX, con->curY, " ");
	con->curOn = curOn;
	return str;
}
