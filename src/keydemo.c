/*
 * C128 CP/M C Library C3L
 *
 * C128 keyboard demo.
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
#include <vdc.h>

/*
 * Copy VDC char set to memory, set screen color, MMU bank, VIC bank, screen
 * memory and char set memory. Clear screen and color memory then enable screen.
 */
void init(uchar *chr) {
    /* Clear CIA 1 ICR status */
    inp(cia1Icr);
    /* Clear all CIA 1 IRQ enable bits */
    outp(cia1Icr, 0x7f);
    /* Set CIA 1 DDRs for keyboard scan */
    outp(cia1DdrA, 0xff);
    outp(cia1DdrB, 0x00);
    /* Black screen and border */
    outp(vicBorderCol, 0);
    outp(vicBgCol0, 0);
    /* Clear color to black */
    clearScrCol(0);
    /* Clear screen */
    clearScr(32);
    /* Copy VDC alt char set to VIC mem */
    copyVdcChrMem(chr, 0x3000, 256);
    /* Set standard character mode using MMU bank 1 and VIC bank 0 */
    setVicChrMode(1, 0, (ushort) scrMem / 1024, (ushort) chr / 2048);
    /* Clear color to white */
    clearScrCol(1);
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
    clearScrCol(0);
    /* CPM default */
    setVicChrMode(0, 0, 11, 3);
    /* Enable CIA 1 IRQ */
    outp(cia1Icr, 0x82);
}

/*
 * Wait for Return.
 */
void waitKey() {
    printCol(0, 24, 1, "Press Return");
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
 * Simple screen line editor.
 */
void readLine() {
    char *str;
    clearScr(32);
    clearScrCol(1);
    printCol(0, 0, 14, "Type in line and press return:");
    str = readVicLine(0, 2, 40);
    printCol(0, 4, 14, "You entered:");
    printCol(0, 6, 13, str);
    free(str);
    waitKey(scrMem);
}

/*
 * Display low level key scan and decoded key.
 */
void keyboard() {
    char str[40];
    uchar *ciaKeyScan, exitKey;
    clearScr(32);
    clearScrCol(1);
    print(4, 0, "Standard and extended key scan");
    printCol(0, 2, 14, " 0  1  2  3  4  5  6  7  8  9 10");
    printCol(0, 6, 3, "Key pressed:");
    printCol(0, 24, 1, "Press Return");
    do {
        ciaKeyScan = getKeys();
        exitKey = ciaKeyScan[0];
        sprintf(str, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
                ciaKeyScan[0], ciaKeyScan[1], ciaKeyScan[2], ciaKeyScan[3],
                ciaKeyScan[4], ciaKeyScan[5], ciaKeyScan[6], ciaKeyScan[7],
                ciaKeyScan[8], ciaKeyScan[9], ciaKeyScan[10]);
        print(0, 4, str);
        free(ciaKeyScan);
        scrMem[253] = decodeKey();
    } while (exitKey != 0xfd);
}

/*
 * Run demo.
 */
void run(uchar *chr, uchar *vicMem) {
    char str[40];
    print(0, 0, "Low level key scan of standard and      "
            "extended keyboard. You can also decode  "
            "unshifted and shifted characters. CIA 1 "
            "interrupts are disabled, so as not to   "
            "disrupt the key scan.");
    sprintf(str, "vicMem: %04x", vicMem);
    print(0, 6, str);
    sprintf(str, "chrMem: %04x", chrMem);
    print(0, 7, str);
    sprintf(str, "scrMem: %04x", scrMem);
    print(0, 8, str);
    waitKey();
    keyboard();
    readLine();
}

main() {
    /* Program is small enough to use left over bank 0 memory */
    uchar *vicMem = allocVicMem(0);
    /* Use space after ROM character set for RAM character set */
    uchar *chr = (uchar *) 0x3000;
    /* Use ram after character set for screen */
    uchar *scr = (uchar *) 0x3800;
    /* Save screen/border color */
    uchar border = inp(vicBorderCol);
    uchar background = inp(vicBgCol0);
	scrWidth = 40;
	scrHeight = 25;
    scrSize = scrWidth * scrHeight;
    scrMem = scr;
    scrColMem = (uchar *) vicColMem;
    chrMem = chr;
    /* Set screen functions */
    clearScr = clearVicScr;
    clearScrCol = clearVicCol;
    /* Use VIC print functions */
    print = printVic;
    printCol = printVicCol;
    init(chr);
    run(chr, vicMem);
    free(vicMem);
    done(border, background);
}
