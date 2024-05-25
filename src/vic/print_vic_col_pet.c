/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <screen.h>
#include <vic.h>

/*
 * Print PETSCII with color.
 */
void printVicColPet(const screen *scr, const unsigned char x, const unsigned char y, const unsigned char color, const char *str) {
	asciiToPet(str);
	printVicCol(scr, x, y, scr->color[color], str);
}
