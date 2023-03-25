/*
 * C128 8563 VDC.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

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
#define vdcScrSize 2000   /* VDC screen size in bytes */
#define vdcBmpSize 16000  /* VDC bitmap size in bytes */

#define vdcBmpSize 16000      /* 640x200 screen size in bytes */
#define vdcOddFldOfs 21360    /* 640 X 480 interlace odd field offset */

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
extern void fillVdcMem(ushort vdcMem, ushort len, uchar value);
extern void copyVdcChrMem(uchar *mem, ushort vdcMem, ushort chars);
extern void copyVdcMemChr(uchar *mem, ushort vdcMem, ushort chars);
extern void clearVdcScr(uchar c);
extern void clearVdcCol(uchar c);
extern void printVdc(uchar x, uchar y, char *str);
extern void printVdcCol(uchar x, uchar y, uchar color, char *str);
extern void setVdcBmpMode(ushort dispPage, ushort attrPage);
extern void clearVdcBmp(uchar c);
extern void clearVdcBmpCol(uchar c);
extern void setVdcPix(ushort x, ushort y);
extern void clearVdcPix(ushort x, ushort y);
extern void drawVdcLineH(ushort x, ushort y, ushort len,
        uchar setPix);
extern void drawVdcLineV(ushort x, ushort y, ushort len,
        uchar setPix);
extern void printVdcBmp(uchar x, uchar y, char *str);
