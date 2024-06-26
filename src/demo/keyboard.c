/*
 * C128 CP/M real time key press decode.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <screen.h>
#include <sid.h>
#include <stdio.h>
#include <stdlib.h>
#include <demo.h>

/*
 * Display low level key scan and decoded key.
 * Also display joysticks and paddles.
 */
void keyboard(const screen *scr) {
	char str[40];
	unsigned char exitKey, key, x1, y1, x2, y2, mx1, my1, mx2, my2;
	unsigned char *ciaKeyScan = (unsigned char*) malloc(11);
	/* Clear screen to spaces */
	(scr->clearScr)(scr, 32);
	/* Clear color to white */
	(scr->clearScrCol)(scr, scrWhite);
	(scr->print)(scr, (scr->scrWidth - 30) / 2, 0, "Standard and extended key scan");
	(scr->printCol)(scr, (scr->scrWidth - 32) / 2, 2, scrLightBlue, " 0  1  2  3  4  5  6  7  8  9 10");
	(scr->printCol)(scr, 0, 6, scrCyan, "Key pressed:");
	(scr->printCol)(scr, 0, 7, scrCyan, "Joystick 1:");
	(scr->printCol)(scr, 0, 8, scrCyan, "Joystick 2:");
	(scr->printCol)(scr, 0, 9, scrCyan, "Paddle 1:");
	(scr->printCol)(scr, 0, 10, scrCyan, "Paddle 2:");
	(scr->printCol)(scr, 0, 24, scrYellow, "Press Return");
	do {
		getKeys(ciaKeyScan);
		exitKey = ciaKeyScan[0];
		sprintf(str, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", ciaKeyScan[0], ciaKeyScan[1], ciaKeyScan[2],
				ciaKeyScan[3], ciaKeyScan[4], ciaKeyScan[5], ciaKeyScan[6], ciaKeyScan[7], ciaKeyScan[8], ciaKeyScan[9],
				ciaKeyScan[10]);
		(scr->print)(scr, (scr->scrWidth - 32) / 2, 4, str);
		key = decodeKey();
		if (key == 0) {
			key = 32;
		}
		sprintf(str, "%c", key);
		(scr->print)(scr, 13, 6, str);
		sprintf(str, "%02x", getJoystick1());
		(scr->print)(scr, 13, 7, str);
		sprintf(str, "%02x", getJoystick2());
		(scr->print)(scr, 13, 8, str);
		readSidPots(&x1, &y1, &x2, &y2);
		readSidMouse(&mx1, &my1, &mx2, &my2);
		sprintf(str, "%02x, %02x %02x, %02x", x1, y1, mx1, my1);
		(scr->print)(scr, 13, 9, str);
		sprintf(str, "%02x, %02x %02x, %02x", x2, y2, mx2, my2);
		(scr->print)(scr, 13, 10, str);
	} while (exitKey != 0xfd);
	free(ciaKeyScan);
}
