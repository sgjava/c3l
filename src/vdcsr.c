/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>
#include "hitech.h"
#include "sys.h"

/*
 * VDC registers to save and restore.
 */
uchar vdcSavedRegs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 20, 21,
		22, 23, 24, 25, 26, 27, 28, 29, 34, 35, 36 };

/*
 * Saved registers.
 */
uchar vdcRegs[sizeof(vdcSavedRegs) - 1];

/*
 * Save key VDC registers.
 */
void saveVdc() {
	uchar i;
	for (i = 0; i < sizeof(vdcRegs); i++)
		vdcRegs[i] = inVdc(vdcSavedRegs[i]);
}

/*
 * Restore key VDC registers.
 */
void restoreVdc() {
	uchar i;
	for (i = 0; i < sizeof(vdcRegs); i++)
		outVdc(vdcSavedRegs[i], vdcRegs[i]);
}
