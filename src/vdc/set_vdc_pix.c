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
void setVdcPix(bitmap *bmp, unsigned int x, unsigned int y, unsigned char color) {
	/* Call assembler code */
	setVdcPixAsm(x, y, bmp->color[color], (unsigned int) bmp->bmpMem);
}
