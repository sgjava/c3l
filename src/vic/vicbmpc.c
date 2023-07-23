/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>
#include <string.h>

/*
 * Print with foreground/background color.
 */
void printVicBmpCol(bitmap *bmp, uchar x, uchar y, uchar color, char *str) {
	ushort *bmp16 = (ushort*) bmp->bmpMem;
	ushort *chr16 = (ushort*) bmp->bmpChrMem;
	ushort bmpOfs = (y * 160) + (x * 4);
	ushort colOfs = (y * bmp->scrWidth) + x;
	ushort len = strlen(str);
	ushort i, chrOfs, destOfs;
	uchar c;
	for (i = 0; i < len; i++) {
		chrOfs = str[i] << 2;
		destOfs = i << 2;
		bmp->bmpColMem[colOfs + i] = color;
		for (c = 0; c < 4; c++) {
			bmp16[bmpOfs + destOfs + c] = chr16[chrOfs + c];
		}
	}
}
