/*
 * C128 CP/M 8564/8566 VIC-IIe save registers.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <hitech.h>
#include <sys.h>

/*
 * VIC registers to save and restore.
 */
static uchar vicSavedRegs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
		14, 15, 16, 17, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
		35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46 };

/*
 * Saved registers.
 */
uchar vicRegs[sizeof(vicSavedRegs) - 1];

/*
 * Save key VIC registers.
 */
void saveVic() {
	uchar i;
	for (i = 0; i < sizeof(vicRegs); i++) {
		vicRegs[i] = inp(0xd000 + vicSavedRegs[i]);
	}
}

/*
 * Restore key VIC registers.
 */
void restoreVic() {
	uchar i;
	for (i = 0; i < sizeof(vicRegs); i++) {
		outp(0xd000 + vicSavedRegs[i], vicRegs[i]);
	}
}
