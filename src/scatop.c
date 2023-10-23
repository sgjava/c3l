/*
 * C128 CP/M text abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <stdlib.h>
#include <string.h>

/*
 * Convert string from ASCII to PETSCII.
 */
void asciiToPet(char *str) {
	ushort len = strlen(str);
	ushort i;
	for (i = 0; i < len; i++) {
		if ((str[i] > 96) && (str[i] <= 127)) {
			str[i] = str[i] - 96;
		}
	}
}
