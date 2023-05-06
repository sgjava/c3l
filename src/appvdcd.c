/*
 * C128 CP/M 8563 VDC screen functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include "vdc.h"

/*
 * Restore VDC registers, screen color, screen memory and char set memory location for CP/M return.
 */
void doneVdc() {
	restoreVdc();
	/* ADM-3A clear-home cursor */
	putchar(0x1a);
}
