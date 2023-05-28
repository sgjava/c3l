/*
 * C128 8564/8566 VIC-IIe.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _VIC_H
#define _VIC_H

#include <bitmap.h>
#include <hitech.h>
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
#define vicExtKey      0xd02f /* Extended keyboard scan register */
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
#define vdcLightGray  15

extern uchar* allocVicMem(uchar maxBank);
extern void setVicMmuBank(uchar mmuRcr);
extern void setVicBank(uchar vicBank);
extern void fillVicMem(uchar *mem, ushort len, uchar value);
extern void fillVicMemCol(ushort address, ushort length, uchar color);
extern void setVicMode(uchar ecm, uchar bmm, uchar mcm);
extern void setVicScrMem(uchar scrLoc);
extern void setVicChrMem(uchar chrLoc);
extern void setVicChrMode(uchar mmuRcr, uchar vicBank, uchar scrLoc,
uchar chrLoc);
extern void clearVicScr(screen *scr, uchar c);
extern void clearVicCol(screen *scr, uchar c);
extern void printVic(screen *scr, uchar x, uchar y, char *str);
extern void printVicCol(screen *scr, uchar x, uchar y, uchar color, char *str);
extern void printVicPet(screen *scr, uchar x, uchar y, char *str);
extern void printVicColPet(screen *scr, uchar x, uchar y, uchar color,
		char *str);
extern void scrollVicUpY(screen *scr, uchar y1, uchar y2);
extern void scrollVicUpYCol(screen *scr, uchar y1, uchar y2);
extern void scrollVicUpAsm(ushort start, uchar length, uchar lines);
extern void scrollVicUpColAsm(ushort start, uchar length, uchar lines);
extern void scrollVicUp(screen *scr, uchar x1, uchar y1, uchar x2, uchar y2);
extern void scrollVicUpCol(screen *scr, uchar x1, uchar y1, uchar x2, uchar y2);
extern char* readVicLine(screen *scr, uchar x, uchar y, uchar len);
extern void setVicBmpMem(uchar bmpLoc);
extern void setVicBmpMode(uchar mmuRcr, uchar vicBank, uchar scrLoc,
uchar bmpLoc);
extern void clearVicBmp(bitmap *bmp, uchar c);
extern void clearVicBmpCol(bitmap *bmp, uchar c);
extern void setVicPix(bitmap *bmp, ushort x, ushort y, uchar color);
extern void drawVicLineH(bitmap *bmp, ushort x, ushort y, ushort len,
uchar color);
extern void drawVicLineV(bitmap *bmp, ushort x, ushort y, ushort len,
uchar color);
extern void printVicBmp(bitmap *bmp, uchar x, uchar y, char *str);
extern void printVicBmpCol(bitmap *bmp, uchar x, uchar y, uchar color,
		char *str);
extern void configVicSpr(screen *scr, uchar *spr, uchar sprNum, uchar sprCol);
extern void enableVicSpr(uchar sprNum);
extern void disableVicSpr(uchar sprNum);
extern void setVicSprLoc(uchar sprNum, ushort x, uchar y);
extern void setVicSprFg(uchar sprNum);
extern void setVicSprBg(uchar sprNum);
extern void initVicScr(screen *scr, ushort scrMem, ushort chrMem);
extern void initVicScrMode(screen *scr, uchar bgCol, uchar fgCol, uchar chrCol);
extern void initVicBmp(bitmap *bmp, ushort bmpMem, ushort colMem, ushort chrMem);
extern void initVicBmpMode(bitmap *bmp, uchar bgCol, uchar fgCol, uchar pixCol);
extern void doneVic(uchar bgCol, uchar fgCol);

#endif
