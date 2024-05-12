/*
 * C128 8563 VDC.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _VDC_H
#define _VDC_H

#include <sys/compiler.h>
#include <bitmap.h>
#include <screen.h>

#define vdcStatusReg 0xD600    /* VDC status register */
#define vdcDataReg   0xD601    /* VDC data register */

#define vdcHzTotal          0  /* VDC internal registers */
#define vdcHzDisp           1
#define vdcHzSyncPos        2
#define vdcVtHzSyncWidth    3
#define vdcVtTotal          4
#define vdcVtTotalAdj       5
#define vdcVtDisp           6
#define vdcVtSyncPos        7
#define vdcIlaceMode        8
#define vdcChTotalVt        9
#define vdcCurStScanLine   10
#define vdcCurEndScanLine  11
#define vdcDspStAddrHi     12
#define vdcDspStAddrLo     13
#define vdcCurPosHi        14
#define vdcCurPosLo        15
#define vdcLightPenVt      16
#define vdcLightPenHz      17
#define vdcUpdAddrHi       18
#define vdcUpdAddrLo       19
#define vdcAttrStAddrHi    20
#define vdcAttrStAddrLo    21
#define vdcChDspHz         22
#define vdcChDspVt         23
#define vdcVtSmScroll      24
#define vdcHzSmScroll      25
#define vdcFgBgColor       26
#define vdcAddrIncPerRow   27
#define vdcChSetStAddr     28
#define vdcUlScanLineCnt   29
#define vdcWordCnt         30
#define vdcCPUData         31
#define vdcBlkCpySrcAddrHi 32
#define vdcBlkCpySrcAddrLo 33
#define vdcDispEnableSt    34
#define vdcDispEnableEnd   35
#define vdcRamRefresh      36

#define vdcBlack        0      /* VDC RGB colors */
#define vdcDarkGray     1
#define vdcDarkBlue     2
#define vdcLightBlue    3
#define vdcDarkGreen    4
#define vdcLightGreen   5
#define vdcDarkCyan     6
#define vdcLightCyan    7
#define vdcDarkRed      8
#define vdcLightRed     9
#define vdcDarkPurple  10
#define vdcLightPurple 11
#define vdcDarkYellow  12
#define vdcLightYellow 13
#define vdcMedGray     14
#define vdcWhite       15

#define vdcAltChrSet 0x80      /* VDC text mode attribute bits */
#define vdcRvsVid    0x40
#define vdcUnderline 0x20
#define vdcBlink     0x10
#define vdcRed       0x08
#define vdcGreen     0x04
#define vdcBlue      0x02
#define vdcIntensity 0x01

#define vdcCurSolid  0         /* VDC cursor modes */
#define vdcCurNone   1
#define vdcCurRate16 2
#define vdcCurRate32 3

#define vdcMaxBlock      255   /* VDC character set */
#define vdcCharsPerSet   256
#define vdcMaxCharBytes  32

#define vdcScrMem 0x0000  /* VDC default screen memory */
#define vdcColMem 0x0800  /* VDC default attribute memory */
#define vdcChrMem 0x2000  /* VDC default character set memory */

extern void __LIB__ saveVdc();
extern void __LIB__ restoreVdc();
extern unsigned char __LIB__ inVdc(unsigned char regNum) __z88dk_fastcall;
extern void __LIB__ outVdc(unsigned char regNum, unsigned char regVal);
extern void __LIB__ setVdcDspPage(unsigned int dispPage, unsigned int attrPage);
extern void __LIB__ setVdcFgBg(unsigned char f, unsigned char b);
extern void __LIB__ setVdcAttrsOn();
extern void __LIB__ setVdcAttrsOff();
extern void __LIB__ setVdcCursor(unsigned char top, unsigned char bottom, unsigned char mode);
extern void __LIB__ orVdcByte(unsigned int vdcMem, unsigned char value);
extern void __LIB__ andVdcByte(unsigned int vdcMem, unsigned char value);
extern void __LIB__ fillVdcMem(unsigned char *mem, unsigned int len, unsigned char value);
extern void __LIB__ copyVdcChrMem(unsigned char *mem, unsigned int vdcMem, unsigned int chars);
extern void __LIB__ copyVdcMemChr(unsigned char *mem, unsigned int vdcMem, unsigned int chars);
extern void __LIB__ clearVdcScr(screen *scr, unsigned char c);
extern void __LIB__ clearVdcScrCol(screen *scr, unsigned char c);
extern void __LIB__ printVdc(screen *scr, unsigned char x, unsigned char y, char *str);
extern void __LIB__ printVdcCol(screen *scr, unsigned char x, unsigned char y, unsigned char color, char *str);
extern void __LIB__ scrollVdcUpY(screen *scr, unsigned char y1, unsigned char y2);
extern void __LIB__ scrollVdcUpYCol(screen *scr, unsigned char y1, unsigned char y2);
extern void __LIB__ scrollVdcUp(screen *scr, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
extern void __LIB__ scrollVdcUpCol(screen *scr, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
extern void __LIB__ setVdcBmpMode(unsigned int dispPage, unsigned int attrPage);
extern void __LIB__ copyVdcMem(unsigned int source, unsigned int dest, unsigned int len);
extern void __LIB__ clearVdcBmp(bitmap *bmp, unsigned char c);
extern void __LIB__ clearVdcBmpCol(bitmap *bmp, unsigned char c);
extern void __LIB__ setVdcPix(bitmap *bmp, unsigned int x, unsigned int y, unsigned char color);
extern void __LIB__ setVdcPixAsm(unsigned int x, unsigned int y, unsigned char color, unsigned int bmpMem) __smallc;
extern void __LIB__ drawVdcLineH(bitmap *bmp, unsigned int x, unsigned int y, unsigned int len,
unsigned char color);
extern void __LIB__ drawVdcLineV(bitmap *bmp, unsigned int x, unsigned int y, unsigned int len,
unsigned char color);
extern void __LIB__ printVdcBmp(bitmap *bmp, unsigned char x, unsigned char y, char *str);
extern void __LIB__ printVdcBmpCol(bitmap *bmp, unsigned char x, unsigned char y, unsigned char color,
		char *str);
extern void __LIB__ initVdcScr(screen *scr, unsigned int scrMem, unsigned int chrMem);
extern void __LIB__ initVdcScrMode(screen *scr, unsigned char bgCol, unsigned char fgCol, unsigned char chrCol);
extern void __LIB__ initVdcBmp(bitmap *bmp, unsigned int bmpMem, unsigned int colMem, unsigned char *chrMem);
extern void __LIB__ initVdcBmpMode(bitmap *bmp, unsigned char *chrMem, unsigned char bgCol, unsigned char fgCol);
extern void __LIB__ copyVdcToStr(screen* scr, unsigned int offest, char *str, unsigned int len);
extern void __LIB__ vdcChrMemToFile(unsigned int vdcMem, unsigned int chars, char *fileName);
extern void __LIB__ doneVdc();

#endif
