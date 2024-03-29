/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <vdc.h>

/*
 * Fast fill using block writes.
 */
void fillVdcMem(uchar *mem, ushort len, uchar value) {
	uchar blocks, remain;
	register uchar i;
	outVdc(vdcUpdAddrHi, (uchar) ((ushort) mem >> 8));
	outVdc(vdcUpdAddrLo, (uchar) (ushort) mem);
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
