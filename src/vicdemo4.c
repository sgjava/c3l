/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe sprite demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys.h>
#include <hitech.h>
#include <cia.h>
#include <vic.h>
#include <screen.h>
#include <sid.h>

/*
 * Sprite data.
 */
uchar sprData[] = { 0x00, 0x7e, 0x00, 0x03, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x1f,
        0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x3f, 0xff, 0xfc, 0x7f, 0xff, 0xfe, 0x7f,
        0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0x3f,
        0xff, 0xfc, 0x1f, 0xff, 0xf8, 0x1f, 0xff, 0xf8, 0x07, 0xff, 0xe0, 0x03,
        0xff, 0xc0, 0x00, 0x7e, 0x00 };

/*
 * Set screen color, MMU bank, VIC bank, screen memory and char set memory.
 * Clear screen and color memory then enable screen.
 */
void init(uchar *scr, uchar *chr) {
    uchar vicBank = (ushort) scr / 16384;
    clearSid();
    /* Clear all CIA 1 IRQ enable bits */
    outp(cia1Icr, 0x7f);
    /* Clear CIA 1 ICR status */
    inp(cia1Icr);
    /* Clear all CIA 2 IRQ enable bits */
    outp(cia2Icr, 0x7f);
    /* Clear CIA 2 ICR status */
    inp(cia2Icr);
    /* Set CIA 1 DDRs for keyboard scan */
    outp(cia1DdrA, 0xff);
    outp(cia1DdrB, 0x00);
    /* Set screen and border color */
    outp(vicBorderCol, 13);
    outp(vicBgCol0, 0);
    /* Clear color to black */
    clearCol(0);
    /* Clear screen */
    clearScr(32);
    /* Set standard character mode using MMU bank 1 and set VIC based on scr location */
    setVicChrMode(1, vicBank, ((ushort) scr - (vicBank * 16384)) / 1024,
            ((ushort) chr - (vicBank * 16384)) / 2048);
    /* Clear color to white */
    clearCol(1);
    /* Enable screen */
    outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(uchar bgCol, uchar fgCol) {
    clearSid();
    outp(vicBorderCol, bgCol);
    outp(vicBgCol0, fgCol);
    /* Clear color to black */
    clearCol(0);
    /* CPM default */
    setVicChrMode(0, 0, 11, 3);
    /* Enable CIA 1 IRQ */
    outp(cia1Icr, 0x82);
}

/*
 * Wait for Return.
 */
void waitKey(uchar *scr) {
    printCol(0, 24, 7, "Press Return");
    /* Debounce */
    while (getKey(0) == 0xfd)
        ;
    while (getKey(0) != 0xfd)
        ;
    /* Debounce */
    while (getKey(0) == 0xfd)
        ;
}

/*
 * Sound effect.
 */
void sound() {
    setSidEnv(sidVoice1, 0, 0, 15, 9);
    setSidFreq(sidVoice1, 200);
    setSidAtt(sidVoice1, sidNoi);
    setSidRel(sidVoice1, sidNoi);
}

/*
 * Bounce sprite around screen.
 */
void bounceSpr(uchar *scr) {
    uchar y = 50, inFront = 0, color = 6, i;
    ushort x = 24;
    int xDir = 1, yDir = 1;
    uchar *spr = (uchar *) ((ushort) scr) - 64;
    /* Store sprite data in VIC memory above screen */
    for (i = 0; i < 63; i++) {
        spr[i] = sprData[i];
    }
    configVicSpr(scr, spr, 0, 6);
    setVicSprLoc(0, x, y);
    enableVicSpr(0);
    printCol(0, 24, 7, "Press Return");
    setSidVol(15, 0);
    /* Bounce sprite until return pressed */
    while (getKey(0) != 0xfd) {
        x += xDir;
        y += yDir;
        if (x > 321) {
            x = 321;
            xDir = -1;
            sound();
        } else if (x < 24) {
            x = 24;
            xDir = 1;
            sound();
        } else if (y > 230) {
            y = 228;
            yDir = -1;
            sound();
        } else if (y < 50) {
            y = 50;
            yDir = 1;
            sound();
        }
        /* Raster off screen? */
        while ((inp(vicCtrlReg1) & 0x80) != 0x80)
            ;
        /* Move sprite */
        setVicSprLoc(0, x, y);
        /* Did sprite collide with text? */
        if ((inp(vicSprFgColl) & 0x01) == 0x01) {
            if (color == 6) {
                color = 2;
                outp(vicSpr0Col, color);
            }
        } else {
            if (color == 2) {
                color = 6;
                outp(vicSpr0Col, color);
            }
        }
        /* Toggle sprite FG/BG mode */
        if (rand() > 32700) {
            if (inFront) {
                inFront = 0;
                setVicSprFg(0);
            } else {
                inFront = 1;
                setVicSprBg(0);
            }
        }
    }
    disableVicSpr(0);
    clearSid();
}

/*
 * Run demo.
 */
void run(uchar *scr, uchar *chr, uchar *vicMem) {
    uchar i;
    char str[40];
    /* Note the use of printVicPet that converts ASCII to PETSCII */
    print(0, 0, "Using ROM character set and one screen  "
            "at the end of VIC bank 0. Sprite is     "
            "located above screen at 0x3bc0.         "
            "Collision detection changes color.");
    for (i = 0; i < 255; i++) {
        scr[i + 280] = i;
    }
    sprintf(str, "vicMem: %04x", vicMem);
    printCol(0, 15, 14, str);
    sprintf(str, "chr:    %04x", chr);
    printCol(0, 16, 14, str);
    sprintf(str, "scr:    %04x", scr);
    printCol(0, 17, 14, str);
    /* Use VIC raster to seed random numbers */
    srand(inp(vicRaster));
    bounceSpr(scr);
}

main() {
    /* Program is small enough to use left over bank 0 memory */
    uchar *vicMem = allocVicMem(0);
    /* Use ROM character set */
    uchar *chr = (uchar *) 0x1800;
    /* Use ram at end of bank */
    uchar *scr = (uchar *) 0x3c00;
    /* Save screen/border color */
    uchar border = inp(vicBorderCol);
    uchar background = inp(vicBgCol0);
    scrSize = vicScrSize;
    scrMem = scr;
    scrColMem = (uchar *) vicColMem;
    chrMem = chr;
    /* Set screen functions */
    clearScr = clearVicScr;
    clearCol = clearVicCol;
    /* Use VIC print functions */
    print = printVicPet;
    printCol = printVicColPet;
    init(scr, chr);
    run(scr, chr, vicMem);
    free(vicMem);
    done(border, background);
}
