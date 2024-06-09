/*
 * C128 8563 VDC general functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <vdc.h>

/*
 * VDC registers to save and restore.
 */
static unsigned char vdcSavedRegs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 34,
		35, 36 };

/*
 * Saved registers.
 */
unsigned char vdcRegs[sizeof(vdcSavedRegs) - 1];

/*
 * Save key VDC registers.
 */
void saveVdc() {
	unsigned char i;
	for (i = 0; i < sizeof(vdcRegs); i++) {
		vdcRegs[i] = inVdc(vdcSavedRegs[i]);
	}
}

/*
 * Restore key VDC registers.
 */
void restoreVdc() {
	unsigned char i;
	for (i = 0; i < sizeof(vdcRegs); i++) {
		outVdc(vdcSavedRegs[i], vdcRegs[i]);
	}
}
