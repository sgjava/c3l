/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <screen.h>
#include <vic.h>
#include "hitech.h"

/*
 * Print PETSCII with color.
 */
void printVicColPet(uchar x, uchar y, uchar color, char *str) {
	char *petStr = asciiToPet(str);
	printVicCol(x, y, color, petStr);
	free(petStr);
}
