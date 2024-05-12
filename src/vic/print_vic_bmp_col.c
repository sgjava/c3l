/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vic.h>
#include <bitmap.h>
#include <string.h>

/*
 * Print with foreground/background color.
 */
void printVicBmpCol(bitmap *bmp, unsigned char x, unsigned char y, unsigned char color, char *str) {
	unsigned int *bmp16 = (unsigned int*) bmp->bmpMem;
	unsigned int *chr16 = (unsigned int*) bmp->bmpChrMem;
	unsigned int bmpOfs = (y * 160) + (x * 4);
	unsigned int colOfs = (y * bmp->scrWidth) + x;
	unsigned int len = strlen(str);
	unsigned int i, chrOfs, destOfs;
	unsigned char c;
	for (i = 0; i < len; i++) {
		chrOfs = str[i] << 2;
		destOfs = i << 2;
		bmp->bmpColMem[colOfs + i] = color;
		for (c = 0; c < 4; c++) {
			bmp16[bmpOfs + destOfs + c] = chr16[chrOfs + c];
		}
	}
}
