/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 *  Fast copy using block copy.
 */
void copyVdcMem(unsigned int source, unsigned int dest, unsigned int len) {
	unsigned char blocks, remain;
	unsigned char i;
	outVdc(vdcUpdAddrHi, (unsigned char) (dest >> 8));
	outVdc(vdcUpdAddrLo, (unsigned char) dest);
	outVdc(vdcVtSmScroll, (inVdc(vdcVtSmScroll) | 0x80));
	outVdc(vdcBlkCpySrcAddrHi, (unsigned char) (source >> 8));
	outVdc(vdcBlkCpySrcAddrLo, (unsigned char) source);
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
