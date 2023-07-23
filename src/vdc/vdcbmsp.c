/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <bitmap.h>
#include <vdc.h>

/*
 * Set pixel.
 */
void setVdcPix(bitmap *bmp, ushort x, ushort y, uchar color) {
	/* Call assembler code */
	setVdcPixAsm(x, y, bmp->color[color], (ushort) bmp->bmpMem);
}
