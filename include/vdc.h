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
#define vdcScrIntMem 0x0000  /* VDC interlace default screen memory */
#define vdcColIntMem 0x1000  /* VDC interlace default attribute memory */
#define vdcChrIntMem 0x2000  /* VDC interlace default character set memory */

extern void __LIB__ saveVdc();
extern void __LIB__ restoreVdc();
extern unsigned char __LIB__ inVdc(const unsigned char regNum) __z88dk_fastcall;
extern void __LIB__ outVdc(const unsigned char regNum, const unsigned char regVal);
extern void __LIB__ setVdcDspPage(const unsigned int dispPage, const unsigned int attrPage);
extern void __LIB__ setVdcFgBg(const unsigned char f, const unsigned char b);
extern void __LIB__ setVdcAttrsOn();
extern void __LIB__ setVdcAttrsOff();
extern void __LIB__ setVdcCursor(const unsigned char top, const unsigned char bottom, const unsigned char mode);
extern void __LIB__ orVdcByte(const unsigned int vdcMem, const unsigned char value);
extern void __LIB__ andVdcByte(const unsigned int vdcMem, const unsigned char value);
extern void __LIB__ fillVdcMem(const unsigned char *mem, const unsigned int len, const unsigned char value);
extern void __LIB__ copyVdcChrMem(const unsigned char *mem, const unsigned int vdcMem, const unsigned int chars);
extern void __LIB__ copyVdcMemChr(const unsigned char *mem, const unsigned int vdcMem, const unsigned int chars);
extern void __LIB__ clearVdcScr(const screen *scr, const unsigned char c);
extern void __LIB__ clearVdcScrCol(const screen *scr, const unsigned char c);
extern void __LIB__ printVdc(const screen *scr, const unsigned char x, const unsigned char y, const char *str);
extern void __LIB__ printVdcCol(const screen *scr, const unsigned char x, const unsigned char y, const unsigned char color,
		const char *str);
extern void __LIB__ scrollVdcUpY(const screen *scr, const unsigned char y1, const unsigned char y2);
extern void __LIB__ scrollVdcUpYCol(const screen *scr, const unsigned char y1, const unsigned char y2);
extern void __LIB__ scrollVdcUp(const screen *scr, const unsigned char x1, const unsigned char y1, const unsigned char x2,
		const unsigned char y2);
extern void __LIB__ scrollVdcUpCol(const screen *scr, const unsigned char x1, const unsigned char y1, const unsigned char x2,
		const unsigned char y2);
extern void __LIB__ setVdcBmpMode(const unsigned int dispPage, const unsigned int attrPage);
extern void __LIB__ copyVdcMem(const unsigned int source, const unsigned int dest, const unsigned int len);
extern void __LIB__ clearVdcBmp(const bitmap *bmp, const unsigned char c);
extern void __LIB__ clearVdcBmpCol(const bitmap *bmp, const unsigned char c);
extern void __LIB__ setVdcPix(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned char color);
extern void __LIB__ setVdcPixAsm(const unsigned int x, const unsigned int y, const unsigned char color, const unsigned int bmpMem) __smallc;
extern void __LIB__ drawVdcLineH(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len,
		const unsigned char color);
extern void __LIB__ drawVdcLineV(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned int len, const unsigned char color);
extern void __LIB__ printVdcBmp(const bitmap *bmp, const unsigned char x, const unsigned char y, const char *str);
extern void __LIB__ printVdcBmpCol(const bitmap *bmp, const unsigned char x, const unsigned char y, const unsigned char color, const char *str);
extern void __LIB__ initVdcScr(const screen *scr, const unsigned int scrMem, const unsigned int colMem, const unsigned int chrMem);
extern void __LIB__ initVdcScrMode(const screen *scr, const unsigned char bgCol, const unsigned char fgCol, const unsigned char chrCol);
extern void __LIB__ initVdcBmp(const bitmap *bmp, const unsigned int bmpMem, const unsigned int colMem, const unsigned char *chrMem);
extern void __LIB__ initVdcBmpMode(const bitmap *bmp, const unsigned char *chrMem, const unsigned char bgCol, const unsigned char fgCol);
extern void __LIB__ copyVdcToStr(const screen *scr, const unsigned int offest, const char *str, const unsigned int len);
extern void __LIB__ vdcChrMemToFile(const unsigned int vdcMem, const unsigned int chars, const char *fileName);
extern void __LIB__ doneVdc();
extern void __LIB__ vdcChrMemToFile(const unsigned int vdcMem, const unsigned int chars, const char *fileName);
extern  unsigned char __LIB__ isVdc64k();
extern void __LIB__ setVdc64k();
extern void __LIB__ initVdcIntScr(const screen *scr, const unsigned int scrMem, const unsigned int colMem, const unsigned int chrMem) ;
extern void __LIB__  initVdcIntScrMode(const screen *scr, const unsigned char bgCol, const unsigned char fgCol, const unsigned char chrCol);
extern void __LIB__ initVdcIntBmp(const bitmap *bmp, const unsigned int bmpMem, const unsigned int colMem, const unsigned char *chrMem);
extern void __LIB__ initVdcIntBmpMode(const bitmap *bmp, const unsigned char *chrMem, const unsigned char bgCol, const unsigned char fgCol);
extern void __LIB__ setVdcIntPixAsm(const unsigned int x, const unsigned int y, const unsigned char color, const unsigned int bmpMem) __smallc;
extern void __LIB__ setVdcIntPix(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned char color);

#endif
