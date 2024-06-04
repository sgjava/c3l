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
extern unsigned char __LIB__* allocVicMem(const unsigned char maxBank);
extern void __LIB__ setVicMmuBank(const unsigned char mmuRcr);
extern void __LIB__ setVicBank(const unsigned char vicBank);
extern void __LIB__ fillVicMem(const unsigned char *mem, const unsigned int len, const unsigned char value);
extern void __LIB__ fillVicMemCol(const unsigned int address, const unsigned int length, const unsigned char color) __smallc;
extern void __LIB__ setVicMode(const unsigned char ecm, const unsigned char bmm, const unsigned char mcm);
extern void __LIB__ setVicScrMem(const unsigned char scrLoc);
extern void __LIB__ setVicChrMem(const unsigned char chrLoc);
extern void __LIB__ setVicChrMode(const unsigned char mmuRcr, const unsigned char vicBank, const unsigned char scrLoc,
		const unsigned char chrLoc);
extern void __LIB__ clearVicScr(const screen *scr, const unsigned char c);
extern void __LIB__ clearVicCol(const screen *scr, const unsigned char c);
extern void __LIB__ printVic(const screen *scr, const unsigned char x, const unsigned char y, const char *str);
extern void __LIB__ printVicCol(const screen *scr, const unsigned char x, const unsigned char y, const unsigned char color,
		const char *str);
extern void __LIB__ printVicPet(const screen *scr, const unsigned char x, const unsigned char y, const char *str);
extern void __LIB__ printVicColPet(const screen *scr, const unsigned char x, const unsigned char y, const unsigned char color,
		const char *str);
extern void __LIB__ scrollVicUpY(const screen *scr, const unsigned char y1, const unsigned char y2);
extern void __LIB__ scrollVicUpYCol(const screen *scr, const unsigned char y1, const unsigned char y2);
extern void __LIB__ scrollVicUpAsm(const unsigned int start, const unsigned char length, const unsigned char lines) __smallc;
extern void __LIB__ scrollVicUpColAsm(const unsigned int start, const unsigned char length, const unsigned char lines) __smallc;
extern void __LIB__ scrollVicUp(const screen *scr, const unsigned char x1, const unsigned char y1, const unsigned char x2,
		const unsigned char y2);
extern void __LIB__ scrollVicUpCol(const screen *scr, const unsigned char x1, const unsigned char y1, const unsigned char x2,
		const unsigned char y2);
extern char __LIB__* readVicLine(const screen *scr, const unsigned char x, const unsigned char y, const unsigned char len);
extern void __LIB__ setVicBmpMem(const unsigned char bmpLoc);
extern void __LIB__ setVicBmpMode(const unsigned char mmuRcr, const unsigned char vicBank, const unsigned char scrLoc,
		const unsigned char bmpLoc, const unsigned char mcm);
extern void __LIB__ clearVicBmp(const bitmap *bmp, const unsigned char c);
extern void __LIB__ clearVicBmpCol(const bitmap *bmp, const unsigned char c);
extern void __LIB__ setVicPix(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned char color);
extern void __LIB__ setVicPixAsm(const unsigned int x, const unsigned int y, const unsigned char color, const unsigned int bmpMem) __smallc;
extern void __LIB__ setVicPixMc(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned char color);
extern void __LIB__ drawVicLineH(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len,
		const unsigned char color);
extern void __LIB__ drawVicLineHMc(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len,
		const unsigned char color);
extern void __LIB__ drawVicLineV(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len,
		const unsigned char color);
extern void __LIB__ printVicBmp(const bitmap *bmp, const unsigned char x, const unsigned char y, const char *str);
extern void __LIB__ printVicBmpCol(const bitmap *bmp, const unsigned char x, const unsigned char y, const unsigned char color,
		const char *str);
extern void __LIB__ configVicSpr(const screen *scr, const unsigned char *spr, const unsigned char sprNum,
		const unsigned char sprCol);
extern void __LIB__ enableVicSpr(const unsigned char sprNum);
extern void __LIB__ disableVicSpr(const unsigned char sprNum);
extern void __LIB__ setVicSprLoc(const unsigned char sprNum, const unsigned int x, const unsigned char y);
extern void __LIB__ setVicSprFg(const unsigned char sprNum);
extern void __LIB__ setVicSprBg(const unsigned char sprNum);
extern void __LIB__ initVicScr(const screen *scr, const unsigned int scrMem, const unsigned int chrMem);
extern void __LIB__ initVicScrMode(const screen *scr, const unsigned char bgCol, const unsigned char fgCol,
		const unsigned char chrCol);
extern void __LIB__ initVicBmp(const bitmap *bmp, const unsigned int bmpMem, const unsigned int colMem, const unsigned int chrMem);
extern void __LIB__ initVicBmpMode(const bitmap *bmp, const unsigned char bgCol, const unsigned char fgCol,
		const unsigned char pixCol);
extern void __LIB__ initVicBmpMc(const bitmap *bmp, const unsigned int bmpMem, const unsigned int colMem, const unsigned int chrMem);
extern void __LIB__ initVicBmpModeMc(const bitmap *bmp, const unsigned char bgCol, const unsigned char fgCol, const unsigned char pixCol1,
		const unsigned char pixCol2, const unsigned char pixCol3);
extern void __LIB__ copyVicToStr(const screen *scr, const unsigned int offset, const char *str, const unsigned int len);
extern void __LIB__ vicSplitScr(const unsigned int raster1, const unsigned int ctrlReg1, const unsigned int raster2,
		const unsigned int ctrlReg2) __smallc;
extern void __LIB__ doneVic();

#endif
