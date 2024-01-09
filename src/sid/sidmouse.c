/*
 * C128 6581/8580 SID functions.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <cia.h>
#include <hitech.h>
#include <sid.h>
#include <sys.h>

/*
 * Read 1351 compatible mouse in port 1 and 2 (values are passed by reference).
 *
 * Note CIA 2 timer A is used.
 */
void readMouseSid(uchar *x1, uchar *y1, uchar *x2, uchar *y2) {
	readSidPots(x1, y1, x2, y2);
	/* Change value if noise bit 0 */
	if ((*x1 & 0x01) == 0) {
		*x1 = (*x1 & 0x7f) >> 1;
	}
	/* Change value if noise bit 0 */
	if ((*y1 & 0x01) == 0) {
		*y1 = (*y1 & 0x7f) >> 1;
	}
	/* Change value if noise bit 0 */
	if ((*x2 & 0x01) == 0) {
		*x2 = (*x2 & 0x7f) >> 1;
	}
	/* Change value if noise bit 0 */
	if ((*y2 & 0x01) == 0) {
		*y2 = (*y2 & 0x7f) >> 1;
	}
}
