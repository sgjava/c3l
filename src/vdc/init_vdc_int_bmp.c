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
void initVdcIntBmp(const bitmap *bmp, const unsigned int bmpMem, const unsigned int colMem, const unsigned char *chrMem) {
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
	bmp->bmpHeight = 400;
	bmp->bmpSize = ((unsigned long) bmp->bmpWidth * bmp->bmpHeight) / 8;
	bmp->scrWidth = 80;
	bmp->scrHeight = 50;
	bmp->colors = 2;
	bmp->pixWidth = 1;
	bmp->bmpColSize = bmp->scrWidth * bmp->scrHeight;
	/* Based on NTSC */
	bmp->aspectRatioMul = 5;
	bmp->aspectRatioDiv = 8;
	bmp->clearBmp = clearVdcBmp;
	bmp->clearBmpCol = clearVdcBmpCol;
	bmp->setPixel = setVdcIntPix;
	bmp->drawLineH = drawVdcLineH;
	bmp->drawLineV = drawVdcLineV;
	bmp->printBmp = printVdcBmp;
}
