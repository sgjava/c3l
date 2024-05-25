/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include <vdc.h>

/*
 * Copy VDC character set to memory to a file.
 */
void vdcChrMemToFile(const unsigned int vdcMem, const unsigned int chars, const char *fileName) {
	unsigned char c;
	unsigned int vdcOfs = vdcMem, i;
	unsigned char charBuf[8];
	FILE *file;
	if ((file = fopen(fileName, "wb")) != NULL) {
		for (i = 0; i < chars; i++) {
			outVdc(vdcUpdAddrHi, (unsigned char) (vdcOfs >> 8));
			outVdc(vdcUpdAddrLo, (unsigned char) vdcOfs);
			// Only use 8 bytes of 16 byte character definition
			for (c = 0; c < 8; c++) {
				charBuf[c] = inVdc(vdcCPUData);
			}
			fwrite(charBuf, sizeof(unsigned char), sizeof(charBuf), file);
			vdcOfs += 16;
		}
		fclose(file);
	}
}
