/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vic.h>

/*
 * Initialize bitmap struct for VIC.
 */
void initVicBmpMc(const bitmap *bmp, const unsigned int bmpMem, const unsigned int colMem, const unsigned int chrMem) {
	static unsigned char vicColors[16] = { vicBlack, vicWhite, vicRed, vicCyan,
	vicPurple, vicGreen, vicBlue, vicYellow, vicOrange, vicBrown, vicLightRed,
	vicDarkGray, vicMedGray, vicLightGreen, vicLightBlue, vicLightGray };
	/* Map colors */
	unsigned char i, len = sizeof(vicColors);
	for (i = 0; i < len; i++) {
		bmp->color[i] = vicColors[i];
	}
	/* VIC bitmap configuration */
	bmp->bmpChrMem = (unsigned char*) chrMem;
	bmp->bmpColMem = (unsigned char*) colMem;
	bmp->bmpMem = (unsigned char*) bmpMem;
	bmp->bmpWidth = 160;
	bmp->bmpHeight = 200;
	bmp->bmpSize = ((unsigned long) bmp->bmpWidth * bmp->bmpHeight) / 4;
	bmp->scrWidth = 40;
	bmp->scrHeight = 25;
	bmp->colors = 4;
	bmp->pixWidth = 2;
	bmp->bmpColSize = bmp->scrWidth * bmp->scrHeight;
	/* Based on NTSC */
	bmp->aspectRatioMul = 3;
	bmp->aspectRatioDiv = 2;
	bmp->clearBmp = clearVicBmp;
	bmp->clearBmpCol = clearVicBmpCol;
	bmp->setPixel = setVicPixMc;
	bmp->drawLineH = drawVicLineHMc;
	bmp->drawLineV = drawVicLineVMc;
	bmp->printBmp = printVicBmp;
	bmp->printBmpCol = printVicBmpCol;
}
