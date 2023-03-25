/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe bitmap demo.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys.h>
#include <hitech.h>
#include <cia.h>
#include <vic.h>
#include <graphics.h>

/*
 * Clear bitmap.
 */
void clearBitmap() {
    /* Set to black */
    clearBmpCol(0x00);
    /* Clear bitmap */
    clearBmp(0);
    /* White foreground and black background */
    clearBmpCol(0x10);
}

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and bitmap memory. Clear bitmap memory, color memory then enable screen.
 */
void init() {
    uchar vicBank = (ushort) bmpMem / 16384;
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
    outp(vicBorderCol, 14);
    outp(vicBgCol0, 0);
    /* Clear bitmap */
    clearBitmap();
    /* Copy VDC alt char set to VIC mem */
    copyVdcChrMem(bmpChrMem, 0x3000, 256);
    /* Set standard bitmap mode using MMU bank 1 */
    setVicBmpMode(1, vicBank, ((ushort) bmpColMem - (vicBank * 16384)) / 1024,
            ((ushort) bmpMem - (vicBank * 16384)) / 8192);
    /* Enable screen */
    outp(vicCtrlReg1, (inp(vicCtrlReg1) | 0x10));
}

/*
 * Restore screen color, set MMU bank, VIC bank, screen
 * memory and char set memory location for CP/M return.
 */
void done(uchar bgCol, uchar fgCol) {
    outp(vicBorderCol, bgCol);
    outp(vicBgCol0, fgCol);
    /* Clear color to black */
    clearBmpCol(0x10);
    /* CPM default */
    setVicChrMode(0, 0, 11, 3);
    /* Enable CIA 1 IRQ */
    outp(cia1Icr, 0x82);
}

/*
 * Wait for Return.
 */
void waitKey() {
    printVicBmp(0, 24, 0x36, " Press Return ");
    /* Debounce */
    while (getKey(0) == 0xfd)
        ;
    while (getKey(0) != 0xfd)
        ;
    /* Debounce */
    while (getKey(0) == 0xfd)
        ;
    printVicBmp(0, 24, 0x36, " Erasing pixels ");
}

/*
 * Print centered text on top line in bitmap.
 */
void bannerBmp(char *str) {
    printVicBmp(((40 - strlen(str)) >> 1), 0, 0x36, str);
}

/*
 * Draw lines.
 */
void lines() {
    uchar i;
    bannerBmp(" Bresenham lines ");
    for (i = 0; i < 16; i++) {
        drawLine(0, 0, i * 20, 199, 1);
        drawLine(319, 0, 319 - (i * 20), 199, 1);
    }
    waitKey();
    for (i = 0; i < 16; i++) {
        drawLine(0, 0, i * 20, 199, 0);
        drawLine(319, 0, 319 - (i * 20), 199, 0);
    }
}

/*
 * Draw horizontal lines.
 */
void linesH() {
    uchar i;
    bannerBmp(" Optimized horizontal lines ");
    for (i = 0; i < 159; i++) {
        drawLine(i, i + 20, 319 - i, i + 20, 1);
    }
    waitKey();
    for (i = 0; i < 159; i++) {
        drawLine(i, i + 20, 319 - i, i + 20, 0);
    }
}

/*
 * Draw vertical lines.
 */
void linesV() {
    uchar i;
    bannerBmp(" Optimized vertical lines ");
    for (i = 10; i < 199; i++) {
        drawLine(i + 57, 10, i + 57, i + 1, 1);
    }
    waitKey();
    for (i = 10; i < 199; i++) {
        drawLine(i + 57, 10, i + 57, i + 1, 0);
    }
}

/*
 * Draw Bezier curves.
 */
void bezier() {
    uchar i;
    bannerBmp(" Bezier curves ");
    for (i = 0; i < 35; i++) {
        drawBezier(i * 5, 10, 319, 15 + i * 5, 319, 15 + i * 5, 1);
    }
    waitKey();
    for (i = 0; i < 35; i++) {
        drawBezier(i * 5, 10, 319, 15 + i * 5, 319, 15 + i * 5, 0);
    }
}

/*
 * Draw rectangles.
 */
void rectangles() {
    uchar i;
    bannerBmp(" Rectangles ");
    for (i = 1; i < 30; i++) {
        drawRect(i * 2, i * 2, (i * 10) + 20, (i * 5) + 20, 1);
    }
    waitKey();
    for (i = 1; i < 30; i++) {
        drawRect(i * 2, i * 2, (i * 10) + 20, (i * 5) + 20, 0);
    }
}

/*
 * Draw squares.
 */
void squares() {
    uchar i;
    bannerBmp(" Squares ");
    for (i = 0; i < 10; i++) {
        drawSquare(i * 8, i * 8, (i * 8) + 8, 1);
    }
    waitKey();
    for (i = 0; i < 10; i++) {
        drawSquare(i * 8, i * 8, (i * 8) + 8, 0);
    }
}

/*
 * Draw ellipses.
 */
void ellipses() {
    ushort i;
    bannerBmp(" Ellipses ");
    for (i = 1; i < 9; i++) {
        drawEllipse(159, 99, i * 19, i * 10, 1);
    }
    waitKey();
    for (i = 1; i < 9; i++) {
        drawEllipse(159, 99, i * 19, i * 10, 0);
    }
}

/*
 * Draw circles.
 */
void circles() {
    ushort i;
    bannerBmp(" Circles ");
    for (i = 1; i < 12; i++) {
        drawCircle(159, 99, i * 10, 1);
    }
    waitKey();
    for (i = 1; i < 12; i++) {
        drawCircle(159, 99, i * 10, 0);
    }
}

/*
 * Run demo.
 */
void run(uchar *vicMem) {
    char str[40];
    printVicBmp(0, 0, 0x16,
            "This demo will show off bitmap graphics."
                    "Interrupts are disabled and getKey is   "
                    "used to read keyboard.                  ");
    sprintf(str, "mem: %04x", vicMem);
    printVicBmp(0, 4, 0x12, str);
    sprintf(str, "chr: %04x", bmpChrMem);
    printVicBmp(0, 6, 0x12, str);
    sprintf(str, "scr: %04x", bmpColMem);
    printVicBmp(0, 8, 0x12, str);
    sprintf(str, "bmp: %04x", bmpMem);
    printVicBmp(0, 10, 0x12, str);
    waitKey();
    clearBitmap();
    lines();
    clearBitmap();
    linesH();
    clearBitmap();
    linesV();
    clearBitmap();
    bezier();
    clearBitmap();
    rectangles();
    clearBitmap();
    squares();
    clearBitmap();
    ellipses();
    clearBitmap();
    circles();
}

main() {
    /* We need to use bank 2 since program is over 16K */
    uchar vicBank = 2;
    uchar *vicMem = allocVicMem(vicBank);
    /* Use beginning of bank 2 for RAM character set */
    uchar *chr = (uchar *) 0x8000;
    /* Use ram after character set for screen */
    uchar *scr = (uchar *) 0x8800;
    /* Use bottom of bank 2 for bitmap */
    uchar *bmp = (uchar *) 0xa000;
    /* Save border/background color */
    uchar border = inp(vicBorderCol);
    uchar background = inp(vicBgCol0);
    /* Set default sizes and locations */
    bmpSize = vicBmpSize;
    bmpColSize = vicScrSize;
    bmpMem = bmp;
    bmpColMem = scr;
    bmpChrMem = chr;
    /* Use VIC clear functions */
    clearBmp = clearVicBmp;
    clearBmpCol= clearVicBmpCol;
    /* Use VIC pixel functions */
    setPixel = setVicPix;
    clearPixel = clearVicPix;
    /* Use optimized horizontal and vertical lines on the VIC */
    drawLineH = drawVicLineH;
    drawLineV = drawVicLineV;
    /* VIC aspect ratio */
    aspectRatio = 2;
    init();
    run(vicMem);
    done(border, background);
    free(vicMem);
}
