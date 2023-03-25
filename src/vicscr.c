/*
 * C128 CP/M 8564/8566 VIC-IIe screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdlib.h>
#include <sys.h>
#include <string.h>
#include <hitech.h>
#include <cia.h>
#include <screen.h>
#include <vic.h>

/*
 * Set screen 0-15 memory location (1K per screen).
 */
void setVicScrMem(uchar scrLoc) {
    outp(vicMemCtrl, (inp(vicMemCtrl) & 0x0f) | (scrLoc << 4));
}

/*
 * Set character set 0-7 memory location (2K per character set).
 */
void setVicChrMem(uchar chrLoc) {
    outp(vicMemCtrl, (inp(vicMemCtrl) & 0xf0) | (chrLoc << 1));
}

/*
 * Set standard character mode (no MCM or ECM).
 */
void setVicChrMode(uchar mmuRcr, uchar vicBank, uchar scrLoc, uchar chrLoc) {
    setVicMmuBank(mmuRcr);
    setVicBank(vicBank);
    setVicMode(0, 0, 0);
    setVicScrMem(scrLoc);
    setVicChrMem(chrLoc);
}

/*
 * Clear screen using 16 bit word.
 */
void clearVicScr(uchar c) {
    fillVicMem(scrMem, 0, scrSize >> 1, (c << 8) + c);
}

/*
 * Clear color memory.
 */
void clearVicCol(uchar c) {
    register ushort i;
    for (i = 0; i < scrSize; i++) {
        outp((ushort) scrColMem + i, c);
    }
}

/*
 * Print without color.
 */
void printVic(uchar x, uchar y, char *str) {
    ushort scrOfs = (y * 40) + x;
    ushort len = strlen(str);
    ushort i;
    for (i = 0; i < len; i++) {
        scrMem[scrOfs + i] = str[i];
    }
}

/*
 * Print with color.
 */
void printVicCol(uchar x, uchar y, uchar color, char *str) {
    ushort colOfs = (ushort) scrColMem + (y * 40) + x;
    ushort len = strlen(str);
    ushort i;
    for (i = 0; i < len; i++) {
        outp(colOfs + i, color);
    }
    printVic(x, y, str);
}

/*
 * Print PETSCII without color.
 */
void printVicPet(uchar x, uchar y, char *str) {
    char *petStr = asciiToPet(str);
    printVic(x, y, petStr);
    free(petStr);
}

/*
 * Print PETSCII with color.
 */
void printVicColPet(uchar x, uchar y, uchar color, char *str) {
    char *petStr = asciiToPet(str);
    printVicCol(x, y, color, petStr);
    free(petStr);
}

/*
 * Scroll screen memory up 1 line starting at x for len words.
 */
void scrollVicUpX(uchar x, uchar y, uchar len, uchar lines) {
    register uchar w;
    uchar i;
    ushort *scr16 = (ushort *) scrMem;
    ushort destLine = (y * 20) + x;
    ushort sourceLine = destLine + 20;
    for (i = 0; i < lines; i++) {
        for (w = 0; w < len; w++) {
            scr16[destLine + w] = scr16[sourceLine + w];
        }
        destLine += 20;
        sourceLine = destLine + 20;
    }
}

/*
 * Scroll screen memory up 1 line by number of lines.
 */
void scrollVicUp(uchar y, uchar lines) {
    scrollVicUpX(0, y, 20, lines);
}

/*
 * Use screen memory as simple input line. Only backspace supported, but insert
 * and delete could be added later.
 */
char *readVicLine(uchar x, uchar y, uchar len) {
    uchar strLen;
    char *str;
    uchar keyVal, lastKeyVal, i;
    ushort scrOfs = (y * 40) + x;
    ushort scrMin = scrOfs;
    ushort scrMax = scrMin + len - 1;
    lastKeyVal = 0x00;
    /* Show cursor */
    scrMem[scrOfs] = '_';
    do {
        keyVal = decodeKey();
        /* Debounce if current key equals last key */
        if (keyVal == lastKeyVal) {
            i = 0;
            do {
                /* ~1/60th second delay */
                while (inp(vicRaster) != 0xff)
                    ;
                while (inp(vicRaster) == 0xff)
                    ;
                keyVal = decodeKey();
                i++;
            } while ((keyVal == lastKeyVal) && (i < 8));
        }
        lastKeyVal = keyVal;
        /* Decoded key? */
        if (keyVal != 0x00) {
            /* Backspace? */
            if (keyVal == 0x7f) {
                if (scrOfs > scrMin) {
                    scrMem[scrOfs] = ' ';
                    scrOfs--;
                }
            } else {
                if ((scrOfs <= scrMax) && (keyVal != 0x0d)) {
                    scrMem[scrOfs] = keyVal;
                    scrOfs++;
                }
            }
            /* Show cursor */
            scrMem[scrOfs] = '_';
        }
    } while (keyVal != 0x0d);
    /* Figure out string length based on current screen offset */
    strLen = scrOfs - scrMin;
    str = (char *) malloc(strLen + 1);
    /* Screen to string */
    for (i = 0; i < strLen; i++) {
        str[i] = scrMem[scrMin + i];
    }
    str[strLen] = 0;
    return str;
}
