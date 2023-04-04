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
 * Print PETSCII without color.
 */
void printVicPet(uchar x, uchar y, char *str) {
	char *petStr = asciiToPet(str);
	printVic(x, y, petStr);
	free(petStr);
}
