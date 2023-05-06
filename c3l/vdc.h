/*
 * C128 8563 VDC.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#ifndef _VDC_H
#define _VDC_H

#include "hitech.h"
#include "screen.h"

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
#define vdcMediumGray  14
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

extern void saveVdc();
extern void restoreVdc();
extern uchar inVdc(uchar regNum);
extern void outVdc(uchar regNum, uchar regVal);
extern void setVdcDspPage(ushort dispPage, ushort attrPage);
extern void setVdcFgBg(uchar f, uchar b);
extern void setVdcAttrsOn();
extern void setVdcAttrsOff();
extern void setVdcCursor(uchar top, uchar bottom, uchar mode);
extern void orVdcByte(ushort vdcMem, uchar value);
extern void andVdcByte(ushort vdcMem, uchar value);
extern void fillVdcMem(uchar *mem, ushort len, uchar value);
extern void copyVdcChrMem(uchar *mem, ushort vdcMem, ushort chars);
extern void copyVdcMemChr(uchar *mem, ushort vdcMem, ushort chars);
extern void clearVdcScr(screen* scr, uchar c);
extern void clearVdcScrCol(screen* scr, uchar c);
extern void printVdc(screen* scr, uchar x, uchar y, char *str);
extern void printVdcCol(screen* scr, uchar x, uchar y, uchar color, char *str);
extern void scrollVdcUpY(screen* scr, uchar y1, uchar y2);
extern void scrollVdcUpYCol(screen* scr, uchar y1, uchar y2);
extern void scrollVdcUp(screen* scr, uchar x1, uchar y1, uchar x2, uchar y2);
extern void scrollVdcUpCol(screen* scr, uchar x1, uchar y1, uchar x2, uchar y2);
extern void setVdcBmpMode(ushort dispPage, ushort attrPage);
extern void copyVdcMem(ushort source, ushort dest, ushort len);
extern void clearVdcBmp(screen* scr, uchar c);
extern void clearVdcBmpCol(screen* scr, uchar c);
extern void setVdcPix(screen* scr, ushort x, ushort y, uchar color);
extern void setVdcPixAsm(ushort x, ushort y, uchar color, ushort bmpMem);
extern void drawVdcLineH(screen* scr, ushort x, ushort y, ushort len,
        uchar color);
extern void drawVdcLineV(screen* scr, ushort x, ushort y, ushort len,
        uchar color);
extern void printVdcBmp(screen* scr, uchar x, uchar y, char *str);
extern void printVdcBmpCol(screen* scr, uchar x, uchar y, uchar color, char *str);
extern void initVdcScr(screen *scr, ushort scrMem, ushort chrMem, uchar bgCol, uchar fgCol, uchar chrCol);
extern void doneVdc();

#endif
