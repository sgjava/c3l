/*
 * C128 CP/M text abstraction.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <string.h>

#include "hitech.h"

/*
 * Convert string from ASCII to PETSCII.
 */
char* asciiToPet(char *str) {
	ushort len = strlen(str);
	char *petStr = (char*) malloc(len + 1);
	ushort i;
	for (i = 0; i < len; i++) {
		if ((str[i] > 96) && (str[i] <= 127)) {
			petStr[i] = str[i] - 96;
		} else {
			petStr[i] = str[i];
		}
	}
	petStr[len] = 0;
	return petStr;
}
