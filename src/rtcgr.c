/*
 * DS12C887 - Real Time Clock.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <sys.h>
#include <hitech.h>
#include <rtc.h>

/*
 * Get RTC register.
 */
uchar getRtcReg(uchar reg) {
	outp(rtcRegA, reg);
	return inp(rtcRegB);
}
