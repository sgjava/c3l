/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vic.h>

/*
 * Print PETSCII without color.
 */
void printVicPet(screen *scr, uchar x, uchar y, char *str) {
	asciiToPet(str);
	printVic(scr, x, y, str);
}
