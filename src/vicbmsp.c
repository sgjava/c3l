/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>

/*
 * Set pixel.
 */
void setVicPix(bitmap *bmp, ushort x, ushort y, uchar color) {
	/* Call assembler code */
	setVicPixAsm(x, y, color, (ushort) bmp->bmpMem);
}
