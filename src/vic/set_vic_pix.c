/*
 * C128 CP/M 8564/8566 VIC-IIe bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <bitmap.h>
#include <vic.h>

/*
 * Set pixel.
 */
void setVicPix(const bitmap *bmp, const unsigned int x, const unsigned int y, const unsigned char color) {
	/* Call assembler code */
	setVicPixAsm(x, y, bmp->color[color], (unsigned int) bmp->bmpMem);
}
