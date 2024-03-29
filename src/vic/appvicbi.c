/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <hitech.h>
#include <vic.h>

/*
 * Initialize screen struct for VIC.
 */
void initVicBmp(bitmap *bmp, ushort bmpMem, ushort colMem, ushort chrMem) {
	static uchar vicColors[16] = { vicBlack, vicWhite, vicRed, vicCyan,
	vicPurple, vicGreen, vicBlue, vicYellow, vicOrange, vicBrown, vicLightRed,
	vicDarkGray, vicMedGray, vicLightGreen, vicLightBlue, vicLightGray };
	/* Map colors */
	uchar i, len = sizeof(vicColors);
	for (i = 0; i < len; i++) {
		bmp->color[i] = vicColors[i];
	}
	/* VIC bitmap configuration */
	bmp->bmpChrMem = (uchar*) chrMem;
	bmp->bmpColMem = (uchar*) colMem;
	bmp->bmpMem = (uchar*) bmpMem;
	bmp->bmpWidth = 320;
	bmp->bmpHeight = 200;
	bmp->bmpSize = ((ulong) bmp->bmpWidth * bmp->bmpHeight) / 8;
	bmp->scrWidth = 40;
	bmp->scrHeight = 25;
	bmp->bmpColSize = bmp->scrWidth * bmp->scrHeight;
	/* Based on NTSC */
	bmp->aspectRatioMul = 3;
	bmp->aspectRatioDiv = 4;
	bmp->clearBmp = clearVicBmp;
	bmp->clearBmpCol = clearVicBmpCol;
	bmp->setPixel = setVicPix;
	bmp->drawLineH = drawVicLineH;
	bmp->drawLineV = drawVicLineV;
	bmp->printBmp = printVicBmp;
	bmp->printBmpCol = printVicBmpCol;
}
