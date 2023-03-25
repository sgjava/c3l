/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <string.h>
#include <hitech.h>
#include <vdc.h>

/*
 * VDC registers to save and restore.
 */
uchar vdcSavedRegs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 20, 21,
        22, 23, 24, 25, 26, 27, 28, 29, 34, 35, 36 };

/*
 * Saved registers.
 */
uchar vdcRegs[sizeof(vdcSavedRegs) - 1];

/*
 * Save key VDC registers.
 */
void saveVdc() {
    uchar i;
    for (i = 0; i < sizeof(vdcRegs); i++)
        vdcRegs[i] = inVdc(vdcSavedRegs[i]);
}

/*
 * Restore key VDC registers.
 */
void restoreVdc() {
    uchar i;
    for (i = 0; i < sizeof(vdcRegs); i++)
        outVdc(vdcSavedRegs[i], vdcRegs[i]);
}

/*
 * Read VDC register.
 */
uchar inVdc(uchar regNum) {
    outp(vdcStatusReg, regNum);
    while ((inp(vdcStatusReg) & 0x80) == 0x00)
        ;
    return (inp(vdcDataReg));
}

/*
 * Write VDC register.
 */
void outVdc(uchar regNum, uchar regVal) {
    outp(vdcStatusReg, regNum);
    while ((inp(vdcStatusReg) & 0x80) == 0x00)
        ;
    outp(vdcDataReg, regVal);
}

/*
 * Or VDC byte with value and store it.
 */
void orVdcByte(ushort vdcMem, uchar value) {
    uchar saveByte;
    outVdc(vdcUpdAddrHi, (uchar) (vdcMem >> 8));
    outVdc(vdcUpdAddrLo, (uchar) vdcMem);
    saveByte = inVdc(vdcCPUData);
    outVdc(vdcUpdAddrHi, (uchar) (vdcMem >> 8));
    outVdc(vdcUpdAddrLo, (uchar) vdcMem);
    outVdc(vdcCPUData, saveByte | value);
}

/*
 * And VDC byte with value and store it.
 */
void andVdcByte(ushort vdcMem, uchar value) {
    uchar saveByte;
    outVdc(vdcUpdAddrHi, (uchar) (vdcMem >> 8));
    outVdc(vdcUpdAddrLo, (uchar) vdcMem);
    saveByte = inVdc(vdcCPUData);
    outVdc(vdcUpdAddrHi, (uchar) (vdcMem >> 8));
    outVdc(vdcUpdAddrLo, (uchar) vdcMem);
    outVdc(vdcCPUData, saveByte & value);
}

/*
 * Fast fill using block writes.
 */
void fillVdcMem(ushort vdcMem, ushort len, uchar value) {
    uchar blocks, remain;
    register uchar i;
    outVdc(vdcUpdAddrHi, (uchar) (vdcMem >> 8));
    outVdc(vdcUpdAddrLo, (uchar) vdcMem);
    outVdc(vdcVtSmScroll, (inVdc(vdcVtSmScroll) & 0x7f));
    outVdc(vdcCPUData, value);
    if (len > vdcMaxBlock) {
        blocks = len / vdcMaxBlock;
        remain = len % vdcMaxBlock;
        for (i = 1; i <= blocks; i++)
            outVdc(vdcWordCnt, vdcMaxBlock);
        if (remain > 1)
            outVdc(vdcWordCnt, --remain);
    } else if (len > 1)
        outVdc(vdcWordCnt, --len);
}

/*
 * Copy VDC character set to memory.
 */
void copyVdcChrMem(uchar *mem, ushort vdcMem, ushort chars) {
    register uchar c;
    ushort vdcOfs = vdcMem, memOfs = 0, i;
    for (i = 0; i < chars; i++) {
        outVdc(vdcUpdAddrHi, (uchar) (vdcOfs >> 8));
        outVdc(vdcUpdAddrLo, (uchar) vdcOfs);
        /* Only use 8 bytes of 16 byte character definition */
        for (c = 0; c < 8; c++) {
            mem[memOfs + c] = inVdc(vdcCPUData);
        }
        memOfs += 8;
        vdcOfs += 16;
    }
}

/*
 * Copy character set to VDC memory.
 */
void copyVdcMemChr(uchar *mem, ushort vdcMem, ushort chars) {
    register uchar c;
    ushort vdcOfs = vdcMem, memOfs = 0, i;
    for (i = 0; i < chars; i++) {
        outVdc(vdcUpdAddrHi, (uchar) (vdcOfs >> 8));
        outVdc(vdcUpdAddrLo, (uchar) vdcOfs);
        /* Only use 8 bytes of 16 byte character definition */
        for (c = 0; c < 8; c++) {
            outVdc(vdcCPUData, mem[memOfs + c]);
        }
        memOfs += 8;
        vdcOfs += 16;
    }
}

/*
 * Set bitmap memory location, attribute memory location and bitmap mode.
 */
void setVdcBmpMode(ushort dispPage, ushort attrPage) {
    setVdcDspPage(dispPage, attrPage);
    outVdc(vdcHzSmScroll, inVdc(vdcHzSmScroll) | 0x80);
}
