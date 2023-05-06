/*
 * C128 6526 CIA functions.
 *
 * Keys are mapped the same as getch for the most part.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <stdlib.h>

/*
 * Decode key from getKeys array. Handle shifted and unshifted keys. 0x00 is
 * returned if no keys pressed, unmapped keys pressed or unable to decode.
 */
uchar decodeKey() {
	/*
	 * Key to ASCII code unshifted. Unmapped keys are set to 0x00.
	 */
	static uchar stdKeys[11][8] = { { 0x7f, 0x0d, 0x04, 0x00, 0x00, 0x00, 0x00,
			0x18 }, { '3', 'w', 'a', '4', 'z', 's', 'e', 0x00 }, { '5', 'r',
			'd', '6', 'c', 'f', 't', 'x' }, { '7', 'y', 'g', '8', 'b', 'h', 'u',
			'v' }, { '9', 'i', 'j', '0', 'm', 'k', 'o', 'n' }, { '+', 'p', 'l',
			'-', '.', ':', '@', ',' }, { '\\', '*', ';', 0x00, 0x00, '=', '^',
			'/' }, { '1', 0x00, 0x00, '2', 0x20, 0x00, 'q', 0x00 }, { 0x00, '8',
			'5', 0x09, '2', '4', '7', '1' }, { 0x1b, '+', '-', 0x0a, 0x0d, '6',
			'9', '3' }, { 0x00, '0', '.', 0x05, 0x18, 0x13, 0x04, 0x00 } };

	/*
	 * Key to ASCII code shifted. Unmapped keys are set to 0x00.
	 */
	static uchar shiftKeys[11][8] = { { 0x7f, 0x0d, 0x04, 0x00, 0x00, 0x00,
			0x00, 0x18 }, { '#', 'W', 'A', '$', 'Z', 'S', 'E', 0x00 }, { '%',
			'R', 'D', '&', 'C', 'F', 'T', 'X' }, { '\'', 'Y', 'G', '(', 'B',
			'H', 'U', 'V' }, { ')', 'I', 'J', '0', 'M', 'K', 'O', 'N' }, { '+',
			'P', 'L', '-', '>', '[', '@', '<' }, { '\\', '*', ']', 0x00, 0x00,
			'=', '^', '?' }, { '!', 0x00, 0x00, '"', 0x20, 0x00, 'Q', 0x00 }, {
			0x00, '8', '5', 0x09, '2', '4', '7', '1' }, { 0x1b, '+', '-', 0x0a,
			0x0d, '6', '9', '3' }, { 0x00, '0', '.', 0x05, 0x18, 0x13, 0x04,
			0x00 } };
	register uchar i = 0;
	uchar keyCode = 0x00;
	uchar lsCol, rsCol, col;
	uchar *ciaKeyScan;
	ciaKeyScan = getKeys();
	/* Shift row pressed? */
	if ((ciaKeyScan[1] != 0xff) || (ciaKeyScan[6] != 0xff)) {
		lsCol = getLsKeyCol(ciaKeyScan[1]);
		rsCol = getRsKeyCol(ciaKeyScan[6]);
		/* Left shift plus key in same row? */
		if (lsCol < 7) {
			keyCode = shiftKeys[1][lsCol];
			/* Right shift plus key in same row? */
		} else if ((rsCol < 8) && (rsCol != 4)) {
			keyCode = shiftKeys[6][rsCol];
			/* Only shift pressed? */
		} else if ((ciaKeyScan[1] == 0x7f) || (ciaKeyScan[6] == 0xef)) {
			/* Find first key row */
			while ((i < 11) && (ciaKeyScan[i] == 0xff)) {
				/* Skip left shift or right shift if pressed by themselves */
				if (((i == 0) && (ciaKeyScan[1] == 0x7f))
						|| ((i == 5) && ciaKeyScan[6] == 0xef)) {
					i++;
				}
				i++;
			}
			/* Another key pressed besides shift? */
			if (i < 11) {
				col = getKeyCol(ciaKeyScan[i]);
				/* Make sure key code is valid */
				if (col < 8) {
					keyCode = shiftKeys[i][col];
				}
			}
			/* Row 1 not pressed? */
		} else if (ciaKeyScan[1] == 0xff) {
			col = getKeyCol(ciaKeyScan[6]);
			/* Make sure key code is valid */
			if (col < 8) {
				keyCode = stdKeys[6][col];
			}
		} else {
			/* Row 1 pressed */
			col = getKeyCol(ciaKeyScan[1]);
			/* Make sure key code is valid */
			if (col < 8) {
				keyCode = stdKeys[1][col];
			}
		}
	} else {
		/* No shift rows pressed, so find first key row */
		while ((i < 11) && (ciaKeyScan[i] == 0xff)) {
			i++;
		}
		if (i < 11) {
			col = getKeyCol(ciaKeyScan[i]);
			/* Make sure key code is valid */
			if (col < 8) {
				keyCode = stdKeys[i][col];
			}
		}
	}
	free(ciaKeyScan);
	return keyCode;
}
