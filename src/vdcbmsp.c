/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <screen.h>
#include <vdc.h>

/*
 * Set pixel.
 */
void setVdcPix(screen *scr, ushort x, ushort y, uchar color) {
	/* Call assembler code */
	setVdcPixAsm(x, y, color, (ushort) scr->bmpMem);
}
