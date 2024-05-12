/*
 * C128 8564/8566 VIC-IIe.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _VIC_H
#define _VIC_H

#include <sys/compiler.h>
#include <bitmap.h>
#include <screen.h>

#define vicSpr0X       0xd000 /* Sprite 0 horizontal position register */
#define vicSpr0y       0xd001 /* Sprite 0 vertical position register */
#define vicSpr1X       0xd002 /* Sprite 1 horizontal position register */
#define vicSpr1y       0xd003 /* Sprite 1 vertical position register */
#define vicSpr2X       0xd004 /* Sprite 2 horizontal position register */
#define vicSpr2y       0xd005 /* Sprite 2 vertical position register */
#define vicSpr3X       0xd006 /* Sprite 3 horizontal position register */
#define vicSpr3y       0xd007 /* Sprite 3 vertical position register */
#define vicSpr4X       0xd008 /* Sprite 4 horizontal position register */
#define vicSpr4y       0xd009 /* Sprite 4 vertical position register */
#define vicSpr5X       0xd00a /* Sprite 5 horizontal position register */
#define vicSpr5y       0xd00b /* Sprite 5 vertical position register */
#define vicSpr6X       0xd00c /* Sprite 6 horizontal position register */
#define vicSpr6y       0xd00d /* Sprite 6 vertical position register */
#define vicSpr7X       0xd00e /* Sprite 7 horizontal position register */
#define vicSpr7y       0xd00f /* Sprite 7 vertical position register */
#define vicSprXmsb     0xd010 /* Sprites 0-7 horizontal position (most significant bits) */
#define vicCtrlReg1    0xd011 /* Control/vertical fine scrolling register */
#define vicRaster      0xd012 /* Raster scan-line register */
#define vicLightPenX   0xd013 /* Light pen horizontal position */
#define vicLightPenY   0xd014 /* Light pen vertical position */
#define vicSprEnable   0xd015 /* Sprite enable register */
#define vicCtrlReg2    0xd016 /* Control/horizontal fine scrolling register */
#define vicSprYexp     0xd017 /* Sprite vertical expansion register */
#define vicMemCtrl     0xd018 /* Memory control register */
#define vicIntFlag     0xd019 /* Interrupt flag register */
#define vicIntMask     0xd01a /* Interrupt mask register */
#define vicSprFg       0xd01b /* Sprite-to-foreground priority register */
#define vicSprMcm      0xd01c /* Sprite multicolor mode register */
#define vicSprXexp     0xd01d /* Sprite horizontal expansion register */
#define vicSprColl     0xd01e /* Sprite-sprite collision register */
#define vicSprFgColl   0xd01f /* Sprite-foreground collision register */
#define vicBorderCol   0xd020 /* Border color register */
#define vicBgCol0      0xd021 /* Background color (source 0) register */
#define vicBgCol1      0xd022 /* Background color (source 1) register */
#define vicBgCol2      0xd023 /* Background color (source 2) register */
#define vicBgCol3      0xd024 /* Background color (source 3) register */
#define vicSprMcmCol0  0xd025 /* Sprite multicolor (source 0) register */
#define vicSprMcmCol1  0xd026 /* Sprite multicolor (source 1) register */
#define vicSpr0Col     0xd027 /* Sprite 0 color register */
#define vicSpr1Col     0xd028 /* Sprite 1 color register */
#define vicSpr2Col     0xd029 /* Sprite 2 color register */
#define vicSpr3Col     0xd02a /* Sprite 3 color register */
#define vicSpr4Col     0xd02b /* Sprite 4 color register */
#define vicSpr5Col     0xd02c /* Sprite 5 color register */
#define vicSpr6Col     0xd02d /* Sprite 6 color register */
#define vicSpr7Col     0xd02e /* Sprite 7 color register */
#define vicPcrcr       0xd030 /* Processor clock rate control register */

#define vicColMem 0xd800  /* VIC I/O mapped color memory */
#define vicSprMemOfs 1016 /* Sprite memory pointers offset in screen.  */

#define vicBlack       0      /* VIC colors */
#define vicWhite       1
#define vicRed         2
#define vicCyan        3
#define vicPurple      4
#define vicGreen       5
#define vicBlue        6
#define vicYellow      7
#define vicOrange      8
#define vicBrown       9
#define vicLightRed   10
#define vicDarkGray   11
#define vicMedGray    12
#define vicLightGreen 13
#define vicLightBlue  14
#define vicLightGray  15

extern void __LIB__ saveVic();
extern void __LIB__ restoreVic();
extern unsigned char __LIB__ *allocVicMem(unsigned char maxBank);
extern void __LIB__ setVicMmuBank(unsigned char mmuRcr);
extern void __LIB__ setVicBank(unsigned char vicBank);
extern void __LIB__ fillVicMem(unsigned char *mem, unsigned int len, unsigned char value);
extern void __LIB__ fillVicMemCol(unsigned int address, unsigned int length, unsigned char color) __smallc;
extern void __LIB__ setVicMode(unsigned char ecm, unsigned char bmm, unsigned char mcm);
extern void __LIB__ setVicScrMem(unsigned char scrLoc);
extern void __LIB__ setVicChrMem(unsigned char chrLoc);
extern void __LIB__ setVicChrMode(unsigned char mmuRcr, unsigned char vicBank, unsigned char scrLoc,
unsigned char chrLoc);
extern void __LIB__ clearVicScr(screen *scr, unsigned char c);
extern void __LIB__ clearVicCol(screen *scr, unsigned char c);
extern void __LIB__ printVic(screen *scr, unsigned char x, unsigned char y, char *str);
extern void __LIB__ printVicCol(screen *scr, unsigned char x, unsigned char y, unsigned char color, char *str);
extern void __LIB__ printVicPet(screen *scr, unsigned char x, unsigned char y, char *str);
extern void __LIB__ printVicColPet(screen *scr, unsigned char x, unsigned char y, unsigned char color,
		char *str);
extern void __LIB__ scrollVicUpY(screen *scr, unsigned char y1, unsigned char y2);
extern void __LIB__ scrollVicUpYCol(screen *scr, unsigned char y1, unsigned char y2);
extern void __LIB__ scrollVicUpAsm(unsigned int start, unsigned char length, unsigned char lines) __smallc;
extern void __LIB__ scrollVicUpColAsm(unsigned int start, unsigned char length, unsigned char lines) __smallc;
extern void __LIB__ scrollVicUp(screen *scr, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
extern void __LIB__ scrollVicUpCol(screen *scr, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
extern char __LIB__ *readVicLine(screen *scr, unsigned char x, unsigned char y, unsigned char len);
extern void __LIB__ setVicBmpMem(unsigned char bmpLoc);
extern void __LIB__ setVicBmpMode(unsigned char mmuRcr, unsigned char vicBank, unsigned char scrLoc,
unsigned char bmpLoc);
extern void __LIB__ clearVicBmp(bitmap *bmp, unsigned char c);
extern void __LIB__ clearVicBmpCol(bitmap *bmp, unsigned char c);
extern void __LIB__ setVicPix(bitmap *bmp, unsigned int x, unsigned int y, unsigned char color);
extern void __LIB__ setVicPixAsm(unsigned int x, unsigned int y, unsigned char color, unsigned int bmpMem) __smallc;
extern void __LIB__ drawVicLineH(bitmap *bmp, unsigned int x, unsigned int y, unsigned int len,
unsigned char color);
extern void __LIB__ drawVicLineV(bitmap *bmp, unsigned int x, unsigned int y, unsigned int len,
unsigned char color);
extern void __LIB__ printVicBmp(bitmap *bmp, unsigned char x, unsigned char y, char *str);
extern void __LIB__ printVicBmpCol(bitmap *bmp, unsigned char x, unsigned char y, unsigned char color,
		char *str);
extern void __LIB__ configVicSpr(screen *scr, unsigned char *spr, unsigned char sprNum, unsigned char sprCol);
extern void __LIB__ enableVicSpr(unsigned char sprNum);
extern void __LIB__ disableVicSpr(unsigned char sprNum);
extern void __LIB__ setVicSprLoc(unsigned char sprNum, unsigned int x, unsigned char y);
extern void __LIB__ setVicSprFg(unsigned char sprNum);
extern void __LIB__ setVicSprBg(unsigned char sprNum);
extern void __LIB__ initVicScr(screen *scr, unsigned int scrMem, unsigned int chrMem);
extern void __LIB__ initVicScrMode(screen *scr, unsigned char bgCol, unsigned char fgCol, unsigned char chrCol);
extern void __LIB__ initVicBmp(bitmap *bmp, unsigned int bmpMem, unsigned int colMem, unsigned int chrMem);
extern void __LIB__ initVicBmpMode(bitmap *bmp, unsigned char bgCol, unsigned char fgCol, unsigned char pixCol);
extern void __LIB__ copyVicToStr(screen *scr, unsigned int offset, char *str, unsigned int len);
extern void __LIB__ vicSplitScr(unsigned int raster1, unsigned int ctrlReg1, unsigned int raster2, unsigned int ctrlReg2) __smallc;
extern void __LIB__ doneVic();

#endif
