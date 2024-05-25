/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vdc.h>

/*
 * Set pixel.
 */
void setVdcPix(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned char color) {
	/* Call assembler code */
	setVdcPixAsm(x, y, bmp->color[color], (unsigned int) bmp->bmpMem);
}
