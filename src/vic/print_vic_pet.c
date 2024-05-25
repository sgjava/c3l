/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <screen.h>
#include <vic.h>

/*
 * Print PETSCII without color.
 */
void printVicPet(const screen *scr, const unsigned char x, const unsigned char y, const char *str) {
	asciiToPet(str);
	printVic(scr, x, y, str);
}
