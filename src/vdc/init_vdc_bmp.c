/*
 * C128 CP/M 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Initialize screen struct for VIC.
 */
void initVdcBmp(bitmap *bmp, unsigned int bmpMem, unsigned int colMem, unsigned char *chrMem) {
	static unsigned char vdcColors[16] = { vdcBlack, vdcWhite, vdcDarkRed, vdcLightCyan,
	vdcLightPurple, vdcDarkGreen, vdcDarkBlue, vdcLightYellow,
	vdcDarkPurple, vdcDarkYellow, vdcLightRed, vdcDarkCyan, vdcDarkGray,
	vdcLightGreen, vdcLightBlue, vdcMedGray };
	/* Map colors */
	unsigned char i, len = sizeof(vdcColors);
	for (i = 0; i < len; i++) {
		bmp->color[i] = vdcColors[i];
	}
	/* VDC Screen configuration */
	/* Use the alternate character set 0x0800 offset */
	bmp->bmpChrMem = (unsigned char*) ((unsigned int) chrMem) + 0x0800;
	bmp->bmpColMem = (unsigned char*) colMem;
	bmp->bmpMem = (unsigned char*) bmpMem;
	bmp->bmpWidth = 640;
	bmp->bmpHeight = 200;
	bmp->bmpSize = ((unsigned long) bmp->bmpWidth * bmp->bmpHeight) / 8;
	bmp->scrWidth = 80;
	bmp->scrHeight = 25;
	bmp->bmpColSize = bmp->scrWidth * bmp->scrHeight;
	/* Based on NTSC */
	bmp->aspectRatioMul = 1;
	bmp->aspectRatioDiv = 2;
	bmp->clearBmp = clearVdcBmp;
	bmp->clearBmpCol = clearVdcBmpCol;
	bmp->setPixel = setVdcPix;
	bmp->drawLineH = drawVdcLineH;
	bmp->drawLineV = drawVdcLineV;
	bmp->printBmp = printVdcBmp;
}
