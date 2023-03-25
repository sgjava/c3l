/*
 * C128 CP/M 8564/8566 VIC-IIe sprite functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <vic.h>

/*
 * Sprite table.
 */
uchar sprTable[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

/*
 * Configure sprite.
 */
void configVicSpr(uchar *scr, uchar *spr, uchar sprNum, uchar sprCol) {
    uchar vicBank = (ushort) scr / 16384;
    /* Set sprite memory location */
    scr[vicSprMemOfs + sprNum] = ((ushort) spr - (vicBank * 16384)) / 64;
    /* Sprite color */
    outp(vicSpr0Col + sprNum, sprCol);
}

/*
 * Enable sprite.
 */
void enableVicSpr(uchar sprNum) {
    /* Sprite enable */
    outp(vicSprEnable, inp(vicSprEnable) | sprTable[sprNum]);
}

/*
 * Disable sprite.
 */
void disableVicSpr(uchar sprNum) {
    /* Sprite disable */
    outp(vicSprEnable, inp(vicSprEnable) & ~sprTable[sprNum]);
}

/*
 * Set sprite location.
 */
void setVicSprLoc(uchar sprNum, ushort x, uchar y) {
    /* Set sprite X */
    if (x > 255) {
        outp(vicSprXmsb, inp(vicSprXmsb) | sprTable[sprNum]);
        outp(vicSpr0X + (sprNum << 1), x - 256);
    } else {
        outp(vicSprXmsb, inp(vicSprXmsb) & ~sprTable[sprNum]);
        outp(vicSpr0X + (sprNum << 1), x);
    }
    /* Sprite Y */
    outp(vicSpr0y + (sprNum << 1), y);
}

/*
 * Make sprite appear in foreground.
 */
void setVicSprFg(uchar sprNum) {
    /* Sprite priority */
    outp(vicSprFg, inp(vicSprFg) & ~sprTable[sprNum]);
}

/*
 * Make sprite appear in background.
 */
void setVicSprBg(uchar sprNum) {
    /* Sprite priority */
    outp(vicSprFg, inp(vicSprFg) | sprTable[sprNum]);
}
