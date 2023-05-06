/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <stdlib.h>
#include <vic.h>

/*
 * Print PETSCII with color.
 */
void printVicColPet(screen *scr, uchar x, uchar y, uchar color, char *str) {
	char *petStr = asciiToPet(str);
	printVicCol(scr, x, y, color, petStr);
	free(petStr);
}
