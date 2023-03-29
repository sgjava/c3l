/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <vdc.h>

/*
 *  Fast copy using block copy.
 */
void copyVdcMem(ushort source, ushort dest, ushort len) {
	uchar blocks, remain;
	register uchar i;
	outVdc(vdcUpdAddrHi, (uchar) (dest >> 8));
	outVdc(vdcUpdAddrLo, (uchar) dest);
	outVdc(vdcVtSmScroll, (inVdc(vdcVtSmScroll) | 0x80));
	outVdc(vdcBlkCpySrcAddrHi, (uchar) (source >> 8));
	outVdc(vdcBlkCpySrcAddrLo, (uchar) source);
	if (len > vdcMaxBlock) {
		blocks = len / vdcMaxBlock;
		remain = len % vdcMaxBlock;
		for (i = 1; i <= blocks; i++) {
			outVdc(vdcWordCnt, vdcMaxBlock);
		}
		if (remain > 0) {
			outVdc(vdcWordCnt, remain);
		}
	} else if (len > 0) {
		outVdc(vdcWordCnt, len);
	}
}
