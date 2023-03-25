/*
 * C128 CP/M text abstraction.
 *
 * Screen abstraction uses function pointers to drive text output, thus the
 * same code will work on the VIC and VDC. Technically this code would work
 * with other displays as well. You just need to implement the functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <string.h>
#include <hitech.h>

/*
 * Screen memory location.
 */
uchar *scrMem;

/*
 * Screen size in bytes.
 */
ushort scrSize;

/*
 * Screen color location.
 */
uchar *scrColMem;

/*
 * Character set location.
 */
uchar *chrMem;

/*
 * Clear screen.
 */
void (*clearScr)(uchar);

/*
 * Clear screen color.
 */
void (*clearCol)(uchar);

/*
 * Print text without color.
 */
void (*print)(uchar, uchar, char *);

/*
 * Print text with color.
 */
void (*printCol)(uchar, uchar, uchar, char *);

/*
 * Convert string to from ASCII to PETSCII.
 */
char *asciiToPet(char *str) {
    ushort len = strlen(str);
    char *petStr = (char *) malloc(len + 1);
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
