/*
 * C128 8563 VDC bitmap functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"

/*
 * Set pixel.
 */
void setVdcPix(screen *scr, ushort x, ushort y, uchar color) {
	/* Call assembler code */
	setVdcPixAsm(x, y, color, (ushort) scr->bmpMem);
}
