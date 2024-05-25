/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * Fast fill using block writes.
 */
void fillVdcMem(const unsigned char *mem, const unsigned int len, const unsigned char value) {
	unsigned char blocks, remain;
	unsigned char i;
	outVdc(vdcUpdAddrHi, (unsigned char) ((unsigned int) mem >> 8));
	outVdc(vdcUpdAddrLo, (unsigned char) (unsigned int) mem);
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
