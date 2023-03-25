/*
 * C128 CP/M C Library C3L
 *
 * 8564/8566 VIC-IIe character ROM demo.
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

/*
 * Set screen color, MMU bank, VIC bank, screen memory and char set memory.
 * Clear screen and color memory then enable screen.
 */
void init(uchar *scr, uchar *chr) {
    uchar vicBank = (ushort) scr / 16384;
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
    /* Black screen and border */
    outp(vicBorderCol, 0);
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
void waitKey() {
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
 * Run demo.
 */
void run(uchar *scr, uchar *chr, uchar *vicMem) {
    uchar i;
    char str[40];
    print(0, 0, "Simple character mode using ROM for the "
            "character set and one screen at the end "
            "of VIC bank 0. This leaves about 15K for"
            "your program. Once your program grows   "
            "beyond 0x3c00 you have to move to VIC   "
            "bank 1.");
    for (i = 0; i < 255; i++) {
        scr[i + 280] = i;
    }
    sprintf(str, "vicMem: %04x", vicMem);
    printCol(0, 15, 14, str);
    sprintf(str, "chr:    %04x", chr);
    printCol(0, 16, 14, str);
    sprintf(str, "scr:    %04x", scr);
    printCol(0, 17, 14, str);
    waitKey();
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
    /* Set default sizes and locations */
    scrSize = vicScrSize;
    scrMem = scr;
    scrColMem = (uchar *) vicColMem;
    chrMem = chr;
    /* Set screen functions */
    clearScr = clearVicScr;
    clearCol = clearVicCol;
    /* Use VIC print functions (in this case PETSCII) */
    print = printVicPet;
    printCol = printVicColPet;
    init(scr, chr);
    run(scr, chr, vicMem);
    free(vicMem);
    done(border, background);
}
